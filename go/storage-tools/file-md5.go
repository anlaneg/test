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

func doPartFileMD5(path string, info os.FileInfo) (string, error) {
	fileSize := info.Size()
	const M int64 = 1 * 1024 * 1024
	const K int64 = 1 * 1024
	if fileSize < 8*K {
		return doFileMD5(path)
	} else if fileSize < 1*M {
		//1M
		return doMD5(path, 0, 8*K)
	} else if fileSize < 10*M {
		//bigger than 1M
		return doMD5(path, 0, 8*K)
	} else if fileSize < 100*M {
		//bigger than 10M
		return doMD5(path, 1*M, 8*K)
	} else if fileSize < 1*1024*M {
		// bigger than 100M
		return doMD5(path, 10*M, 8*K)
	} else {
		// bigger than 1G
		return doMD5(path, 100*M, 8*K)
	}
}