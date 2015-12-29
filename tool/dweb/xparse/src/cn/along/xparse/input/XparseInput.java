package cn.along.xparse.input;

import java.io.IOException;
import java.util.Vector;

import org.w3c.dom.Element;
import org.w3c.dom.Node;
import org.w3c.dom.NodeList;

import cn.along.xgen.XGenConfig;
import cn.along.xgen.common.IInputFillerIterator;
import cn.along.xgen.common.IInputStructIterator;
import cn.along.xgen.common.IteratorHelper;
import cn.along.xgen.common.StringUtil;
import cn.along.xgen.common.XGenException;
import cn.along.xparse.XparseBase;
import cn.along.xparse.common.Assert;
import cn.along.xparse.common.DefaultValue;
import cn.along.xparse.common.XparseSyntaxException;
import cn.along.xparse.global.XparseGlobal;
import cn.along.xparse.method.XparseMethod;
import cn.along.xparse.session.XparseSession;
import cn.along.xparse.sql.XparseSql;
import cn.along.xparse.struct.XparseStruct;
import cn.along.xparse.validator.XparseValidator;

/**
 * 
 * <input style="single/array"> <struct name="info" type="struct-type"> <!--
 * 目前数组类型未定义　 byte[] length="用逗号分隔各维度“ dynamic-size="true/false" (解决) -->
 * 
 * <member name="user_name"
 * type="bytion/short/int/long/float/double/boolean/class/byte[]" length="2,3"
 * dynamic-size="true/flase" pass-type="in/out/inout" comment="用户名" default=""
 * /> </struct>
 * 
 * 
 * @author samsung
 * 
 */
public class XparseInput extends XparseBase
{
    private String style;
    private Vector<XparseStruct> structs;
    private Vector<XparseBase> orderTags;

    private XparseInput()
    {
        this.structs = new Vector<XparseStruct>();
        this.orderTags = new Vector<XparseBase>();
    }

    public static XparseInput parse(Element xmlNode)
            throws XparseSyntaxException
    {
        XparseInput input = new XparseInput();
        input.setStyle(DefaultValue.get(xmlNode.getAttribute("style"), "single"));

        NodeList nodes = xmlNode.getChildNodes();
        for (int i = 0; i < nodes.getLength(); ++i)
        {
            Node node = nodes.item(i);
            if (node.getNodeType() == Node.ELEMENT_NODE)
            {
                if ("struct".equals(((Element) node).getTagName()))
                {
                    XparseStruct struct = XparseStruct.parse((Element) node);
                    input.addStruct(struct);
                }
                else if ("sql".equals(((Element) node).getTagName()))
                {
                    XparseSql sql = XparseSql.parse((Element) node);
                    // input.addSql(sql);
                    input.addOrderTag(sql);
                }
                else if ("method".equals(((Element) node).getTagName()))
                {
                    XparseMethod method = XparseMethod.parse((Element) node);
                    input.addOrderTag(method);
                    // throw new XparseSyntaxException("unimplements");
                }
                else if ("validators".equals(((Element) node).getTagName()))
                {
                    XparseValidator validator = XparseValidator
                            .parse((Element) node);
                    input.addOrderTag(validator);
                }
                else if ("session".equals(((Element) node).getTagName()))
                {
                    XparseSession session = XparseSession.parse((Element) node);
                    input.addOrderTag(session);
                }
                else if ("global".equals(((Element) node).getTagName()))
                {
                    XparseGlobal global = XparseGlobal.parse((Element) node);
                    input.addOrderTag(global);
                }
                else
                {
                    throw new XparseSyntaxException(
                            "Unkown tag name in 'input' : '"
                                    + ((Element) node).getTagName() + "'");
                }
            }
        }
        return input;
    }

    private void addOrderTag(XparseBase base)
    {
        this.orderTags.add(base);
    }

    private void addStruct(XparseStruct struct)
    {
        this.structs.add(struct);
    }

    public void setStyle(String style) throws XparseSyntaxException
    {
        Assert.test(style != null, "Input sturct style need {single,array}");
        if ("single".equals(style) || "array".equals(style))
        {
            this.style = style;
        }
        else
        {
            throw new XparseSyntaxException("Unkown input struct style:'"
                    + style + "'");
        }
    }

    public String getStyle()
    {
        return this.style;
    }

    public String createString()
    {
        StringBuilder builder = new StringBuilder();
        builder.append("<input style=\"" + this.style + "\">");
        for (int i = 0; i < this.structs.size(); ++i)
        {
            XparseStruct struct = this.structs.get(i);
            builder.append(struct.createString());
        }
        for (int i = 0; i < this.orderTags.size(); ++i)
        {
            XparseBase base = this.orderTags.get(i);
            builder.append(base.createString());
        }
        builder.append("</input>");
        return builder.toString();
    }

    public void inputStructForEach(Object[] obj, IInputStructIterator iterator)
    {
        int size = this.structs.size();
        for (int i = 0; i < size; ++i)
        {
            IteratorHelper helper = new IteratorHelper(i == 0, (i + 1) == size,
                    i, size);
            iterator.iterator(this, this.structs.elementAt(i), helper, obj);
        }
    }

    public void inputFillerForEach(Object[] obj, IInputFillerIterator iterator)
    {
        int size = this.orderTags.size();
        for (int i = 0; i < this.orderTags.size(); ++i)
        {
            IteratorHelper helper = new IteratorHelper(i == 0, (i + 1) == size,
                    i, size);
            iterator.iterator(this, this.orderTags.elementAt(i), helper, obj);
        }
    }

    @Override
    public String gen(XGenConfig config)
    {

        this.inputStructForEach(new Object[] { config },
                new IInputStructIterator()
                {

                    @Override
                    public void iterator(XparseInput input,
                            XparseStruct struct, IteratorHelper helper,
                            Object[] arg)
                    {
                        XGenConfig config = (XGenConfig) arg[0];
                        String output = struct.gen(config);
                        if (config.out_file_name == null)
                        {
                            throw new XGenException("param error");
                        }

                        try
                        {
                            struct.write_file(config.get_output_dir(),
                                    config.out_file_name, output);
                        }
                        catch (IOException e)
                        {
                            // need delete file ?mebe file exist
                            throw new XGenException("write file fail"
                                    + e.getMessage());
                        }
                    }
                });
        StringBuilder builder = new StringBuilder();
        if (config.state_name == null)
        {
            throw new XGenException("state name unknow");
        }
        String ret = this.gen_inner(config);
        builder.append(ret);
        return builder.toString();
    }

    private String gen_inner(XGenConfig config)
    {
        StringBuilder builder = new StringBuilder();
        builder.append(this.genClassHeader(config.state_name));
        builder.append("{\n");
        builder.append(this.genMemberVariable());
        builder.append(this.genClassContructor(config.state_name));
        builder.append(this.genFillerMethod());
        builder.append("}\n");
        return builder.toString();
    }

    private String genFillerMethod()
    {
        StringBuilder builder = new StringBuilder();

        // create fill function
        this.inputFillerForEach(new Object[] { builder },
                new IInputFillerIterator()
                {

                    @Override
                    public void iterator(XparseInput input, XparseBase xbase,
                            IteratorHelper helper, Object[] arg)
                    {
                        StringBuilder builder = (StringBuilder) arg[0];
                        String result = xbase.genFillFunction(input, helper);
                        if (result != null)
                        {
                            builder.append(result);
                        }
                    }
                });

        builder.append("public void filler() throws DBException\n");
        builder.append("{\n");
        this.inputFillerForEach(new Object[] { builder },
                new IInputFillerIterator()
                {
                    @Override
                    public void iterator(XparseInput input, XparseBase xbase,
                            IteratorHelper helper, Object[] arg)
                    {
                        StringBuilder builder = (StringBuilder) arg[0];
                        String result = xbase.genFillCall(input, helper);
                        if (result != null)
                        {
                            builder.append(result);
                        }
                    }

                });
        builder.append("}\n");
        return builder.toString();
    }

    private String genMemberVariable()
    {
        StringBuilder builder = new StringBuilder();
        this.inputStructForEach(new Object[] { builder },
                new IInputStructIterator()
                {

                    @Override
                    public void iterator(XparseInput input,
                            XparseStruct struct, IteratorHelper helper,
                            Object[] arg)
                    {
                        StringBuilder builder = (StringBuilder) arg[0];
                        builder.append("private "
                                + StringUtil.initialUpper(struct.getType())
                                + " $" + helper.getElementIndex() + ";\n");

                        if (helper.isLastElement())
                        {
                            builder.append("\n");
                        }
                    }
                });
        return builder.toString();
    }

    private String genClassContructor(String fill_name)
    {
        StringBuilder builder = new StringBuilder();
        builder.append("public " + StringUtil.initialUpper(fill_name) + "(");
        this.inputStructForEach(new Object[] { builder },
                new IInputStructIterator()
                {

                    @Override
                    public void iterator(XparseInput input,
                            XparseStruct struct, IteratorHelper helper,
                            Object[] arg)
                    {
                        StringBuilder builder = (StringBuilder) arg[0];
                        builder.append(StringUtil.initialUpper(struct.getType())
                                + " $" + helper.getElementIndex());
                        if (!helper.isLastElement())
                        {
                            builder.append(" , ");
                        }
                    }

                });
        builder.append(")\n");
        builder.append("{\n");
        this.inputStructForEach(new Object[] { builder },
                new IInputStructIterator()
                {
                    @Override
                    public void iterator(XparseInput input,
                            XparseStruct struct, IteratorHelper helper,
                            Object[] arg)
                    {
                        StringBuilder builder = (StringBuilder) arg[0];
                        builder.append("this.$" + helper.getElementIndex()
                                + "=$" + helper.getElementIndex() + ";\n");
                    }

                });

        builder.append("}\n");

        return builder.toString();
    }

    private String genClassHeader(String fill_name)
    {
        StringBuilder builder = new StringBuilder();
        builder.append("import java.util.HashMap;\n");
        builder.append("\n");
        builder.append("import cn.along.condb.api.SimpleDBAccess;\n");
        builder.append("import cn.along.condb.exception.DBException;\n");
        builder.append("public class " + StringUtil.initialUpper(fill_name)
                + "\n");
        return builder.toString();
    }

}
