package main

import (
	//"crypto/md5"
	//"flag"
	"fmt"
	"io"
	"os"
	"path/filepath"
	"strings"
	"sort"
	"strconv"
)

const (
	split_string = "-"
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

func duplicates(fileInfos map[string]*FileInfo) (map[string][]*FileInfo, error) {
	result := make(map[string][]*FileInfo, 0)
	for _, info := range fileInfos {
		result_key := fmt.Sprintf("%s%s%d", info.md5, split_string, info.size)
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

	return result, nil
}

func duplicatesFirst(opt *DupOpt, total *int) (map[string][]*FileInfo, error) {
	filesInfos, err := collectFileInfo(opt)
	if err != nil {
		*total = 0
		return nil, err
	}

	*total = len(filesInfos)
	return duplicates(filesInfos)
}

func collectFileInfoFromMap(mid map[string][]*FileInfo) (map[string]*FileInfo, error) {
	result := make(map[string]*FileInfo, 0)
	for _, array := range mid {
		for _, info := range array {
			var err error
			info.md5, err = doWholeFileMD5(info)
			if err != nil {
				return nil, err
			}
			result[info.path] = info
		}
	}

	return result, nil
}

func duplicatesLast(mid map[string][]*FileInfo) (map[string][]*FileInfo, error) {
	filesInfos, err := collectFileInfoFromMap(mid)
	if err != nil {
		return nil, err
	}

	return duplicates(filesInfos)
}

type DupMD5Keys struct {
	md5Keys []string
}

func newDupMD5Keys() *DupMD5Keys {
	return &DupMD5Keys{md5Keys: make([]string, 0)}
}

func (keys *DupMD5Keys) append(key string) {
	keys.md5Keys = append(keys.md5Keys, key)
}

// Len is part of sort.Interface.
func (keys *DupMD5Keys) Len() int {
	return len(keys.md5Keys)
}

// Swap is part of sort.Interface.
func (keys *DupMD5Keys) Swap(i, j int) {
	keys.md5Keys[i], keys.md5Keys[j] = keys.md5Keys[j], keys.md5Keys[i]
}

// Less is part of sort.Interface.
func (keys *DupMD5Keys) Less(i, j int) bool {
	key_i, key_j := keys.md5Keys[i], keys.md5Keys[j]
	split_i, split_j := strings.Split(key_i,split_string), strings.Split(key_j,split_string)
	
	var size_i, size_j int64
	if len(split_i) < 2 {
		size_i = 0
	} else {
		size_i, _ = strconv.ParseInt(split_i[1], 10, 64)
	}
	
	if len(split_j) < 2 {
		size_j = 0
	} else {
		size_j, _ = strconv.ParseInt(split_j[1], 10, 64)
	}
	
	return size_i < size_j
}

func duplicatesFprint(w io.Writer, result map[string][]*FileInfo) error {
	//collect key
	keys := newDupMD5Keys()
	for key, _ := range result {
		keys.append(key)
	}

	//sort by md5 key
	sort.Sort(keys)
	
	//print
	for _, key := range keys.md5Keys {
		fmt.Fprintf(w, "md5=%s:\n", key)
		v := result[key]
		for _, info := range v {
			fmt.Fprintf(w, "\t*size=%d,path=%s\n", info.size, info.path)
		}
	}
	
	return nil
}
