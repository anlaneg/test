package main

import (
	//"crypto/md5"
	//"flag"
	"fmt"
	//"io"
	"os"
	"path/filepath"
)

type FileInfo struct {
	size int64
	name string
	md5  string
	path string
}

func collectFileInfo(opt *DupOpt) (map[string]*FileInfo, error) {
	filesInfo := make(map[string]*FileInfo, 0)

	for _, path := range opt.src_path {
		path, _ = filepath.Abs(path)
		err := filepath.Walk(path, func(path string, info os.FileInfo, err error) error {
			name := info.Name()
			if "." == name || ".." == name {
				//skip '.','..'
				return nil
			}

			mode := info.Mode()
			if !mode.IsRegular() {
				//skip other file mode
				return nil
			}

			collect := &FileInfo{
				name: name,
				path: path,
				size: info.Size(),
			}

			var e error = nil
			/*
				if opt.cmp_part_data {
					collect.md5, e = doPartFileMD5(path, info)
				} else if opt.cmp_full_data {
					collect.md5, e = doFileMD5(path)
				}*/
			collect.md5, e = doPartFileMD5(path, info)
			if e != nil {
				return fmt.Errorf("search file %s,err=%s", path, e.Error())
			}

			filesInfo[path] = collect
			return nil
		})

		if err != nil {
			return nil, err
		}
	}

	return filesInfo, nil
}

/*func duplicates(opt *DupOpt) (map[string][]*FileInfo, int, error) {
	filesInfo, err := collectFileInfo(opt)
	if err != nil {
		return nil, 0, err
	}

	result := make(map[string][]*FileInfo, 0)
	for _, info := range filesInfo {
		if _, dup := result[info.md5]; !dup {
			result[info.md5] = []*FileInfo{info}
		} else {
			result[info.md5] = append(result[info.md5], info)
		}
		//fmt.Printf("name=%s,size=%d,md5=%s,path=%s\n",info.name,info.size,info.md5,k)
	}

	for key, v := range result {
		if len(v) <= 1 {
			delete(result, key)
		}
	}

	return result, len(filesInfo), nil
}*/

func duplicates(opt *DupOpt) (map[string][]*FileInfo, int, error) {
	filesInfo, err := collectFileInfo(opt)
	if err != nil {
		return nil, 0, err
	}

	result := make(map[string][]*FileInfo, 0)
	for _, info := range filesInfo {
		result_key := fmt.Sprintf("%s-%d", info.md5, info.size)
		if _, dup := result[result_key]; !dup {
			result[result_key] = []*FileInfo{info}
		} else {
			result[result_key] = append(result[result_key], info)
		}
	}

	for key, v := range result {
		if len(v) <= 1 {
			delete(result, key)
		}
	}

	return result, len(filesInfo), nil
}