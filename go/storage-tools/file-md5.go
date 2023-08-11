package main

import (
	"crypto/md5"
	//"flag"
	"fmt"
	"io"
	"os"
	//"path/filepath"
)

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

func fileSizeDispatch(fileSize int64, path string, wholeFunc func(path string) (string, error), partFunc func(path string, offset int64, length int64) (string, error)) (string, error) {
	const M int64 = 1 * 1024 * 1024
	const K int64 = 1 * 1024
	if fileSize < 8*K {
		//less than 8K
		return wholeFunc(path)
	} else if fileSize < 1*M {
		//less than 1M
		return partFunc(path, 0, 8*K)
	} else if fileSize < 10*M {
		//less than 10M
		return partFunc(path, 0, 8*K)
	} else if fileSize < 100*M {
		//less than 100M
		return partFunc(path, 1*M, 8*K)
	} else if fileSize < 1*1024*M {
		// less than 1000M
		return partFunc(path, 10*M, 8*K)
	} else {
		// bigger than 1G
		return partFunc(path, 100*M, 8*K)
	}
}

func doPartFileMD5(path string, info os.FileInfo) (string, error) {
	return fileSizeDispatch(info.Size(), path, doFileMD5, doMD5)
}

func doWholeFileMD5(info *FileInfo) (string, error) {
	wholeFunc := func(path string) (string, error) {
		return info.md5, nil
	}
	
	partFunc := func(path string, offset int64, length int64) (string, error) {
		return doFileMD5(path)
	}
	return fileSizeDispatch(info.size, info.path, wholeFunc, partFunc)
}
