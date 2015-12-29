package cn.along.xgen;

import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;

import cn.along.xgen.common.StringUtil;

public class XGenBase
{
    public String gen(XGenConfig config)
    {
        throw new UnknownError();
    }
    
    public void write_file(String dir,String filename,String context) throws IOException
    {
        File f = new File(dir,filename+".java");
        if(!f.createNewFile())
        {
            //throw new IOException(String.format("file:':%s' exists",f.getCanonicalPath()));
        }
        System.out.println(String.format("Write file '%s'",f.getCanonicalPath()));
        FileOutputStream fos = new FileOutputStream(f);
        fos.write(StringUtil.codeFormat(context).getBytes());
        fos.close();
    }
}
