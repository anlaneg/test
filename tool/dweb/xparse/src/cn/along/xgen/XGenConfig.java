package cn.along.xgen;

import cn.along.xparse.Xparse;

public class XGenConfig
{
    public String out_file_name;
    public String state_name;
    
    private Xparse xparse;

    public XGenConfig(Xparse xparse)
    {
        out_file_name = null;
        this.xparse = xparse;
    }

    public String get_output_dir()
    {
        return this.xparse.get_output_dir();
    }
}
