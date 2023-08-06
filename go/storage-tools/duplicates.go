package main

import (
	"flag"
	"fmt"
	"os"
	"path/filepath"
	"crypto/md5"
	"io"
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

func doFileMD5(path string) (string,error){
	f, err := os.Open(path)
	if err != nil {
		return "",err
	}
	defer f.Close()

	h := md5.New()
	if _, err := io.Copy(h, f); err != nil {
		return "",err
	}

	return fmt.Sprintf("%x",h.Sum(nil)), nil
}

func doPartFileMD5(path string,info os.FileInfo) (string,error){
	f, err := os.Open(path)
	if err != nil {
		return "",err
	}
	defer f.Close()

	h := md5.New()
	if _, err := io.Copy(h, f); err != nil {
		return "",err
	}

	return fmt.Sprintf("%x",h.Sum(nil)), nil
}

func main() {
	argmentsParse()
	if !optGlobal.validator() {
		os.Exit(1)
	}

	type FileInfoCollect struct {
		size int64
		name string
		md5  string
	}

	filesInfo := make(map[string]interface{}, 0)
	for id, path := range optGlobal.src_path {
		path , _ = filepath.Abs(path)
		fmt.Printf("target %d=%s\n", id, path)
		err := filepath.Walk(path, func(path string, info os.FileInfo, err error) error {
			name := info.Name()
			if "." == name || ".." == name {
				fmt.Printf("skip dir %s\n", name)
				return nil
			}

			mode := info.Mode()
			if mode.IsRegular() {
				fileInfoCollect := &FileInfoCollect{
					name:name,
					size:info.Size(),
				}
				var e error = nil
				if optGlobal.cmp_part_data {
					fileInfoCollect.md5,e = doPartFileMD5(path,info)
				} else if optGlobal.cmp_full_data {
					fileInfoCollect.md5,e = doFileMD5(path)
				}
				if e != nil {
					fmt.Printf("search file %s,err=%s\n", path, e.Error())
				} else {
					//fmt.Printf("search file %s,md5=%s\n", path, string(fileInfoCollect.md5))
				}
				filesInfo[path] = fileInfoCollect
				//fmt.Printf("search file %s,name=%s\n", path, name)
				return nil
			}

			return nil
		})
		if err != nil {
			fmt.Println(err.Error())
		} else {
			for k,v := range(filesInfo) {
				info ,ok := v.(*FileInfoCollect)
				if !ok {
					fmt.Printf("error type")
					continue
				}
				
				fmt.Printf("name=%s,size=%d,md5=%s,path=%s\n",info.name,info.size,info.md5,k)
			}
			fmt.Printf("total=%d\n",len(filesInfo))
		}
	}
}
