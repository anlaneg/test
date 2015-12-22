package cn.along.xparse;

import java.io.File;
import java.io.IOException;
import java.util.HashSet;
import java.util.Iterator;
import java.util.Set;

import javax.xml.parsers.DocumentBuilder;
import javax.xml.parsers.DocumentBuilderFactory;
import javax.xml.parsers.ParserConfigurationException;

import org.w3c.dom.Document;
import org.xml.sax.SAXException;

import cn.along.xgen.input.XGenInputFill2;
import cn.along.xparse.common.XparseSyntaxException;
import cn.along.xparse.input.XparseInput;

@SuppressWarnings("serial")
class XparseCommandLineError extends Exception
{
    private String msg;

    public XparseCommandLineError(String msg, String[] args, int idx)
    {
        String tmp = " argment:" + idx + "  args:";
        for (int i = idx; i < args.length; ++i)
        {
            tmp += args[i];
        }
        this.msg = msg + tmp;
    }

    public String getMessage()
    {
        return this.msg;
    }
}

@SuppressWarnings("serial")
class XparseCommandLogicError extends Exception
{
    public XparseCommandLogicError(String msg)
    {
        super(msg);
    }
}

@SuppressWarnings("serial")
class XparseCommandHelper extends Exception
{
    public XparseCommandHelper()
    {
        super();
    }
}

public class Xparse
{
    private Set<String> files;
    private String output_dir;

    public Xparse()
    {
        this.files = new HashSet<String>();
        this.output_dir = null;
    }

    private void args_process(String[] args) throws XparseCommandLineError,
            XparseCommandHelper, XparseCommandLogicError
    {
        for (int i = 0; i < args.length; ++i)
        {
            if ("-d".equals(args[i]) || "-directory".equals(args[i]))
            {
                if (i + 1 >= args.length)
                {
                    throw new XparseCommandLineError("Require directory ",
                            args, i);
                }
                this.add_direcotry(args[i + 1]);
                i++;// skip direcotry
                continue;
            }

            if ("-h".equals(args[i]) || "--help".equals(args[i]))
            {
                throw new XparseCommandHelper();
            }

            if ("-f".equals(args[i]) || "--file".equals(args[i]))
            {
                if (i + 1 >= args.length)
                {
                    throw new XparseCommandLineError("Require file ", args, i);
                }
                this.add_file(args[i + 1]);
                i++;// skip file
                continue;
            }

            if ("-O".equals(args[i]) || "--output".equals(args[i]))
            {
                if (i + 1 >= args.length)
                {
                    throw new XparseCommandLineError(
                            "Require output direcotry ", args, i);
                }

                this.add_output_direcotry(args[i + 1]);
                i++;
                continue;
            }

            throw new XparseCommandLineError("Unkown options ", args, i);
        }
    }

    private void add_output_direcotry(String path) throws XparseCommandLogicError
    {
        if (this.output_dir != null)
        {
            throw new XparseCommandLogicError("--output must not repeat");
        }
       
        File f = new File(path);
        if(!(f.exists() && f.isDirectory()))
        {
            throw new XparseCommandLogicError(String.format("'%s' not exist or is not direcotry",path));
        }
        
        if(!f.canWrite())
        {
            throw new XparseCommandLogicError(String.format("'%s' can't write",path));
        }
        
        this.output_dir = path;
    }

    private void add_file(String path) throws XparseCommandLogicError
    {
        File f = new File(path);
        if(!(f.exists() && f.isFile()))
        {
            throw new XparseCommandLogicError(String.format("'%s' not exist or is not file",path));
        }
        
        if(!f.canRead())
        {
            throw new XparseCommandLogicError(String.format("'%s' can't read",path));
        }
        
        //this.files.add(f.getAbsolutePath());
        try
        {
            this.files.add(f.getCanonicalPath());
        }
        catch (IOException e)
        {
            throw new XparseCommandLogicError(String.format("'%s' get path fail:%s",path,e.getMessage()));
        }
        //this.files.add(f.getName());
    }

    private void add_direcotry(String dir)
    {
        File f = new File(dir);
        if(!(f.exists() && f.isDirectory()))
        {
            System.err.println(String.format("'%s' not exist or is not directory",dir));
            return;
        }
        
        this.add_direcotry(f);
    }

    private void add_direcotry(File f)
    {
        File[] find = f.listFiles();
        for(int i = 0 ; i < find.length; ++i)
        {
            if(find[i].getName().endsWith(".xml"))
            {
                try
                {
                    this.add_file(find[i].getAbsolutePath());
                    continue;
                }
                catch (XparseCommandLogicError e)
                {
                   System.err.println(e.getMessage() + " ,ingore the file");
                }
            }
            
            //File dir = new File(find[i]);
            if(find[i].isDirectory())
            {
                this.add_direcotry(find[i]);
            }
        }
    }

    private void print_help(String pro_name, String error_msg)
    {
        String help_text = "Usage: %s [-d <dir-path> | -f <file-path>] -D <output-dir>\n"
                + "Options:\n"
                + "   -d,--directory      Add directory dir to the list of directories to be searched for compile\n"
                + "   -h,--elp           Display this information\n"
                + "   -O,--output         Place the output into <file>\n"
                + "   -f,--file           Compile the source file\n";
        if (error_msg != null)
        {
            help_text = error_msg +"\n\n"+ help_text;
        }

        System.err.println(String.format(help_text, pro_name));
    }

    /**
     * 提供如下命令行：
     * －d，--dir 指定需要查找的目录 可重复
     * －f, --file 指定要编译的文件　可重复
     * －D, --output-dir
     * 指定要输出的位置 --debug ?添加相应日志？
     * 
     * @param args
     */
    public static void main(String[] args)
    {
        Xparse parse = new Xparse();
        try
        {
            parse.args_process(args);
        }
        catch(XparseCommandLogicError e)
        {
            parse.print_help("Xparse", e.getMessage());
            System.exit(1);
        }
        catch (XparseCommandLineError e)
        {
            parse.print_help("Xparse", e.getMessage());
            System.exit(1);
        }
        catch (XparseCommandHelper e)
        {
            parse.print_help("Xparse", null);
            System.exit(1);
        }

        parse.complie();
    }

    private void complie_file(String xml_path)
    {
		try
		{
			Document document = null;
			DocumentBuilderFactory builderFactory = DocumentBuilderFactory
					.newInstance();
			DocumentBuilder builder = builderFactory.newDocumentBuilder();
			File xml = new File(xml_path);
			document = builder.parse(xml);
			//temp code
			if(xml.getName().startsWith("input"))
			{
				XparseInput base = XparseInput.parse(document.getDocumentElement());
				System.out.println(XGenInputFill2.gen(base));
				
			}
			else
			{
				System.err.println(String.format("'%s' file will be ignored.",xml_path));
			}
		}
		catch(Exception e)
		{
			System.err.println(String.format("'%s' file complie fail,will be ignored.",xml_path));
		}
    }
    
    private void complie()
    {
        Iterator<String> iter = this.files.iterator();
        while(iter.hasNext())
        {
            String xml_path=iter.next();
            System.out.println(String.format("....process file %s",xml_path));
            this.complie_file(xml_path);
        }
    }
}
