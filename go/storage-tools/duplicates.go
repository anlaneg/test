package main

import (
	"crypto/md5"
	"flag"
	"fmt"
	"io"
	"os"
	//"path/filepath"
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
	cmp_name      bool
	cmp_size      bool
	cmp_full_data bool
	cmp_part_data bool
	output_path   string
	src_path      []string
}

var (
	optGlobal = &DupOpt{
		cmp_name:      false,
		cmp_size:      false,
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
	flag.BoolVar(&optGlobal.cmp_name, "n", false, "compare with file name")
	flag.BoolVar(&optGlobal.cmp_name, "names", false, "compare with file name")

	flag.BoolVar(&optGlobal.cmp_size, "s", false, "compare with file size")
	flag.BoolVar(&optGlobal.cmp_size, "size", false, "compare with file size")

	flag.BoolVar(&optGlobal.cmp_part_data, "d", true, "compare with file part data")
	flag.BoolVar(&optGlobal.cmp_part_data, "part-data", true, "compare with file part data")

	flag.BoolVar(&optGlobal.cmp_full_data, "f", false, "compare with file full data")
	flag.BoolVar(&optGlobal.cmp_full_data, "full-data", false, "compare with file full data")

	flag.StringVar(&optGlobal.output_path, "o", "", "output path")
	flag.StringVar(&optGlobal.output_path, "output", "", "output path")

	flag.Parse()

	for _, path := range flag.Args() {
		stat, err := os.Stat(path)
		if err != nil {
			fmt.Printf("os.Stat error %s\n", err.Error())
			continue
		}

		mode := stat.Mode()
		if !mode.IsDir() && !mode.IsRegular() {
			fmt.Printf("path %s error\n", path)
			continue
		}

		fmt.Printf("add path: %s\n", path)
		optGlobal.src_path = append(optGlobal.src_path, path)
	}

	//TODO 文件路径去重
}

func (opt *DupOpt) validator() bool {
	if opt.cmp_full_data && (opt.cmp_name || opt.cmp_size || opt.cmp_part_data) {
		fmt.Println("option -n/--names,-s/--size,-d/--part-data will be ignore")
		opt.cmp_name = false
		opt.cmp_size = false
		opt.cmp_part_data = false
	}

	if opt.output_path == "" {
		//fmt.Printf("option -o/--output required,use -o %s\n", c_OUTPUT_PATH)
		opt.output_path = c_OUTPUT_PATH
	}

	if !opt.cmp_full_data && !opt.cmp_name && !opt.cmp_size && !opt.cmp_part_data {
		fmt.Printf("option -n/--names | -s/--size | -f/--full-data | -d/--part-data miss", c_OUTPUT_PATH)
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

func doFileMD5(path string) (string, error) {
	f, err := os.Open(path)
	if err != nil {
		return "", err
	}
	defer f.Close()

	h := md5.New()
	if _, err := io.Copy(h, f); err != nil {
		return "", err
	}

	return fmt.Sprintf("%x", h.Sum(nil)), nil
}

func doMD5(path string, offset int64, length int64) (string, error) {
	f, err := os.Open(path)
	if err != nil {
		return "", err
	}
	defer f.Close()

	secReader := io.NewSectionReader(f, offset, length)
	h := md5.New()
	if _, err := io.Copy(h, secReader); err != nil {
		return "", err
	}

	return fmt.Sprintf("%x", h.Sum(nil)), nil
}

func doPartFileMD5(path string, info os.FileInfo) (string, error) {
	fileSize := info.Size()
	const M int64 = 1 * 1024 * 1024
	if fileSize < 1*M {
		//1M
		return doFileMD5(path)
	} else if fileSize < 10*M {
		//bigger than 1M
		return doMD5(path, 0, 1*M)
	} else if fileSize < 100*M {
		//bigger than 10M
		return doMD5(path, 5*M, 1*M)
	} else if fileSize < 1*1024*M {
		// bigger than 100M
		return doMD5(path, 50*M, 1*M)
	} else {
		// bigger than 1G
		return doMD5(path, 100*M, 1*M)
	}
}

func main() {
	argmentsParse()
	if !optGlobal.validator() {
		os.Exit(1)
	}

	result, totalFiles, err := duplicates(optGlobal)
	if err != nil {
		fmt.Printf("error:%s", err.Error())
		os.Exit(1)
	}

	for key, v := range result {
		fmt.Printf("md5=%s:\n", key)
		for _, info := range v {
			fmt.Printf("\t*size=%d,path=%s\n", info.size, info.path)
		}
		//fmt.Println()
	}

	fmt.Printf("total=%d\n", totalFiles)
}
