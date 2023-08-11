package main

import (
	//"crypto/md5"
	"flag"
	"fmt"
	//"io"
	"os"
	"path/filepath"
)

const (
	c_OUTPUT_PATH = "./duplicates.output"
)

/*
* duplicates [ -n/--names | -s/--size | -f/--full-data | -d/--part-data | -o/--output DIFF-FILES-LISTS ] [ <SRC-PATHS>| DIFF-FILES-LISTS ]
* SRC-PATHS ::= <path>
* DIFF-FILES-LISTS ::= <path>
 */

type DupOpt struct {
	//cmp_name      bool
	//cmp_size      bool
	cmp_full_data bool
	cmp_part_data bool
	output_path   string
	src_path      []string
}

var (
	optGlobal = &DupOpt{
		//cmp_name:      false,
		//cmp_size:      false,
		cmp_full_data: false,
		cmp_part_data: true,
		output_path:   c_OUTPUT_PATH,
	}
)

func pathExists(path string) (bool, error) {
	_, err := os.Stat(path)
	if err == nil {
		return true, nil
	}
	if os.IsNotExist(err) {
		return false, nil
	}
	return false, err
}

func pathExistsError(err error, exists bool) string {
	if err != nil {
		return err.Error()
	}

	if exists {
		return "exist"
	}

	return "unkown"
}

func argmentsParse() {
	flag.BoolVar(&optGlobal.cmp_part_data, "p", true, "compare with file part data")
	flag.BoolVar(&optGlobal.cmp_part_data, "part-data", true, "compare with file part data")

	flag.BoolVar(&optGlobal.cmp_full_data, "f", false, "compare with file full data")
	flag.BoolVar(&optGlobal.cmp_full_data, "full-data", false, "compare with file full data")

	flag.StringVar(&optGlobal.output_path, "o", "", "output path")
	flag.StringVar(&optGlobal.output_path, "output", "", "output path")

	flag.Parse()

	set := make(map[string]int,0)
	for _, p := range flag.Args() {
		path, err := filepath.Abs(p)
		if err != nil {
			fmt.Printf("ignore invalid path :%s\n", p)
			continue 
		}
		
		stat, err := os.Lstat(path)
		if err != nil {
			fmt.Printf("os.Stat error %s\n", err.Error())
			continue
		}

		mode := stat.Mode()
		if mode.Type() & os.ModeSymlink != 0 {
			path , err = os.Readlink(path)
			if err != nil {
				fmt.Printf("Symlink path %s error\n", path)
				continue
			} else {
				fmt.Printf("replace symlink %s to %s\n", p, path)
			}
			
			stat, err = os.Stat(path)
			if err != nil {
				fmt.Printf("os.Stat error %s\n", err.Error())
				continue
			}
			mode = stat.Mode()
		}
		
		if !mode.IsDir() && !mode.IsRegular(){
			fmt.Printf("path %s error\n", path)
			continue
		}
		
		//fmt.Printf("%s mode:%s, is symlink %d\n",path, mode.String(), mode.Type() & os.ModeSymlink)
		set[path] = 1
	}

	for src := range set {
		fmt.Printf("add path: %s\n", src)
		optGlobal.src_path = append(optGlobal.src_path, src)
	}
}

func (opt *DupOpt) validator() bool {
	if opt.cmp_full_data && opt.cmp_part_data {
		fmt.Println("option -d/--part-data will be ignore")
		opt.cmp_part_data = false
	}

	if opt.output_path == "" {
		//fmt.Printf("option -o/--output required,use -o %s\n", c_OUTPUT_PATH)
		opt.output_path = c_OUTPUT_PATH
	}

	if !opt.cmp_full_data && !opt.cmp_part_data {
		fmt.Printf("option -f/--full-data | -d/--part-data miss", c_OUTPUT_PATH)
		return false
	}

	exists, err := pathExists(opt.output_path)
	if err != nil || exists {
		fmt.Printf("option -o/--output '%s' error:%s\n", pathExistsError(err, exists))
		return false
	}

	if len(opt.src_path) == 0 {
		fmt.Printf("option <SRC-PATHS>| DIFF-FILES-LISTS required\n")
		return false
	}

	return true
}

func main() {
	argmentsParse()
	if !optGlobal.validator() {
		os.Exit(1)
	}

	var totalFiles int = 0
	result, err := duplicatesFirst(optGlobal, &totalFiles)
	if err != nil {
		fmt.Printf("error:%s", err.Error())
		os.Exit(1)
	}

	if optGlobal.cmp_full_data && len(result) > 0 {
		result, err = duplicatesLast(result)
		if err != nil {
			fmt.Printf("error:%s", err.Error())
			os.Exit(1)
		}
	}
	
	duplicatesFprint(os.Stdout, result)

	fmt.Printf("duplicates=%d,total=%d\n", len(result), totalFiles)
}
