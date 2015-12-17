package cn.along.xparse.sql;

import java.util.Vector;

import org.w3c.dom.Element;
import org.w3c.dom.Node;
import org.w3c.dom.NodeList;

import cn.along.xgen.common.IteratorHelper;
import cn.along.xgen.common.XgenException;
import cn.along.xgen.common.XgenUnSupportException;
import cn.along.xparse.XparseBase;
import cn.along.xparse.common.Assert;
import cn.along.xparse.common.XparseSyntaxException;
import cn.along.xparse.input.XparseInput;
import cn.along.xparse.parameter.XparseParameter;

/**
 * <!-- 1. sql语句是否需要包含多条sql (不需要) 
 *       2. 是否应实现两类标签来表示input,output (不需要) 
 *       3. 结果集如何map * ?(强制规定格式) 
 *   --> 
 *       <sql name=""> <select/insert/delete/update/proc></select>
 *      <param type="string" >$INPUT.user_name</param> </sql>
 * 
 * @author samsung
 *
 */
public class XparseSql extends XparseBase
{
    private String name;
    private String sql;
    private String type;

    private Vector<XparseParameter> params;

    private XparseSql()
    {
        this.params = new Vector<XparseParameter>();
    }

    public static XparseSql parse(Element xmlNode) throws XparseSyntaxException
    {
        Assert.test(xmlNode.getTagName().equals("sql"));
        XparseSql sql = new XparseSql();
        String name = xmlNode.getAttribute("name");
        Assert.test(name != null && !"".equals(name),
                "<sql> tag must have name attribute");
        sql.setName(name);

        NodeList nodes = xmlNode.getChildNodes();
        for (int i = 0; i < nodes.getLength(); ++i)
        {
            Node node = nodes.item(i);
            if (node.getNodeType() == Node.ELEMENT_NODE)
            {
                if ("select".equals(((Element) node).getTagName()))
                {
                    sql.setType("select");
                    sql.setSql(((Element) node).getTextContent());
                }
                else if ("insert".equals(((Element) node).getTagName()))
                {
                    sql.setType("insert");
                    sql.setSql(((Element) node).getTextContent());
                }
                else if ("delete".equals(((Element) node).getTagName()))
                {
                    sql.setType("delete");
                    sql.setSql(((Element) node).getTextContent());
                }
                else if ("update".equals(((Element) node).getTagName()))
                {
                    sql.setType("update");
                    sql.setSql(((Element) node).getTextContent());
                }
                else if ("proc".equals(((Element) node).getTagName()))
                {
                    sql.setType("proc");
                    sql.setSql(((Element) node).getTextContent());

                }
                else if ("param".equals(((Element) node).getTagName()))
                {
                    XparseParameter parameter = XparseParameter
                            .parse((Element) node);
                    sql.addParameter(parameter);
                }
                else
                {
                    throw new XparseSyntaxException("Unkown sql style:'"
                            + ((Element) node).getTagName() + "'");
                }
            }
        }

        return sql;
    }

    private void addParameter(XparseParameter parameter)
    {
        this.params.add(parameter);
    }

    private void setSql(String textContent)
    {
        this.sql = textContent;
    }

    private void setType(String string)
    {
        this.type = string;
    }

    private void setName(String attribute)
    {
        this.name = attribute;
    }

    public String createString()
    {
        StringBuilder builder = new StringBuilder();
        builder.append("<sql name=\"" + this.name + "\">");
        builder.append("<" + this.type + ">" + this.sql + "</" + this.type
                + ">");
        for (int i = 0; i < this.params.size(); ++i)
        {
            XparseParameter param = this.params.get(i);
            builder.append(param.createString());
        }
        builder.append("</sql>");
        return builder.toString();
    }

    private void createSqlLoadFunctionInnert(StringBuilder builder,
            XparseInput input) throws XgenException
    {
        if ("select".equals(this.type))
        {
            this.createSelectSqlLoadFunction(builder, input);
        }
        else if ("insert".equals(this.type) || "delete".equals(this.type)
                || "update".equals(this.type))
        {
            this.createUpdateSqlLoadFunction(builder, input);
        }
        else if ("proc".equals(this.type))
        {
            // this.createProcSqlLoadFunction(builder);
            throw new XgenUnSupportException();
        }
        else
        {
            throw new XgenUnSupportException();
        }
    }

    private void createUpdateSqlLoadFunction(StringBuilder builder,
            XparseInput input) throws XgenException
    {
        if (input.getStyle() == "array")
        {
            throw new XgenUnSupportException();
        }
        else
        {
            builder.append("\tString sql=\"" + this.sql + "\";\n");
            if (this.params.size() > 0)
            {
                builder.append("\tHashMap<String,Object> param = new HashMap<String,Object>()\n");
                for (int i = 0; i < this.params.size(); ++i)
                {
                    XparseParameter xparameter = this.params.elementAt(i);
                    // String type = xparameter.getType();
                    String name = xparameter.getName();
                    String value = xparameter.getValue();
                    builder.append("\tparam.put(\"" + name + "\"" + ", \""
                            + value + "\")\n");
                }
            }
            builder.append("\tSimpleDBAccess.update(sql, this.$0, this.$0,"
                    + ((this.params.size() > 0) ? "param" : "null") + ");\n");
        }
    }

    private void createSelectSqlLoadFunction(StringBuilder builder,
            XparseInput input) throws XgenException
    {
        if (input.getStyle() == "array")
        {
            throw new XgenUnSupportException();
        }
        else
        {
            builder.append("\tString sql=\"" + this.sql + "\";\n");
            if (this.params.size() > 0)
            {
                builder.append("\tHashMap<String,Object> param = new HashMap<String,Object>()\n");
                for (int i = 0; i < this.params.size(); ++i)
                {
                    XparseParameter xparameter = this.params.elementAt(i);
                    // String type = xparameter.getType();
                    String name = xparameter.getName();
                    String value = xparameter.getValue();
                    builder.append("\tparam.put(\"" + name + "\"" + ", \""
                            + value + "\")\n");
                }
            }
            builder.append("\tSimpleDBAccess.loadOne(sql, this.$0, this.$0,"
                    + ((this.params.size() > 0) ? "param" : "null") + ");\n");
        }
    }

    /**
     * 通过sql语句的执行结果来填充结构体
     * 
     * @return
     * @throws XgenException
     */
    public String createSqlLoadFunction(XparseInput input) throws XgenException
    {
        StringBuilder builder = new StringBuilder();

        // gen function head
        builder.append("public void sqlload_" + this.name + "()\n");
        builder.append("{\n");
        this.createSqlLoadFunctionInnert(builder, input);
        builder.append("}\n");
        return builder.toString();
    }

    public String createSqlParameter(String prefix, XparseInput input)
            throws XgenException
    {
        // StringBuilder builder = new StringBuilder();
        throw new XgenUnSupportException();
        // return "";
    }

    private String genUpdateFillFunction(XparseInput input,
            IteratorHelper helper)
    {
        StringBuilder builder = new StringBuilder();
        builder.append("private void ");
        builder.append(this.get_update_fill_function_name());
        builder.append("()\n{\n");
        builder.append("String sql=\"" + this.sql + "\";\n");
        if (this.params.size() > 0)
        {
            builder.append("HashMap<String,Object> param = new HashMap<String,Object>()\n");
            for (int i = 0; i < this.params.size(); ++i)
            {
                XparseParameter xparameter = this.params.elementAt(i);
                // String type = xparameter.getType();
                String name = xparameter.getName();
                String value = xparameter.getValue();
                builder.append("param.put(\"" + name + "\"" + ", \"" + value
                        + "\")\n");
            }
        }
        builder.append("SimpleDBAccess.update(sql, this.$0, this.$0,"
                + ((this.params.size() > 0) ? "param" : "null") + ");\n");
        builder.append("}\n");
        return builder.toString();

    }

    private String genSelectFillFunction(XparseInput input,
            IteratorHelper helper)
    {
        StringBuilder builder = new StringBuilder();
        builder.append("private void ");
        builder.append(this.get_select_fill_function_name());
        builder.append("()\n{\n");
        builder.append("String sql=\"" + this.sql + "\";\n");
        //if sql have param and no <param> tag give,use $0
        if (this.params.size() > 0)
        {
            builder.append("HashMap<String,Object> param = new HashMap<String,Object>();\n");
            for (int i = 0; i < this.params.size(); ++i)
            {
                XparseParameter xparameter = this.params.elementAt(i);
                // String type = xparameter.getType();
                String name = xparameter.getName();
                String value = xparameter.getValue();
                builder.append("\tparam.put(\"" + name + "\"" + ", \"" + value
                        + "\")\n");
            }
        }
        builder.append("SimpleDBAccess.loadOne(sql, this.$0, this.$0,"
                + ((this.params.size() > 0) ? "param" : "null") + ");\n");
        builder.append("}\n");
        return builder.toString();
    }

    @Override
    public String genFillFunction(XparseInput input, IteratorHelper helper)
            throws XgenException
    {
        if ("select".equals(this.type))
        {
            return this.genSelectFillFunction(input, helper);
        }
        else if ("insert".equals(this.type) || "update".equals(this.type) || "delete".equals(this.type))
        {
            return this.genUpdateFillFunction(input, helper);
        }
        return null;
    }

    private String get_select_fill_function_name()
    {
        return "sql_select_" + this.name;
    }

    private String get_update_fill_function_name()
    {
        return "sql_" + this.type + "_" + this.name;
    }

    private String genSelectFillCall(XparseInput input, IteratorHelper helper)
    {
        return "this." + this.get_select_fill_function_name() + "();\n";
    }

    private String genUpdateFillCall(XparseInput input, IteratorHelper helper)
    {
        return "this." + this.get_update_fill_function_name() + "();\n";
    }

    @Override
    public String genFillCall(XparseInput input, IteratorHelper helper)
            throws XgenException
    {
        if ("select".equals(this.type))
        {
            return this.genSelectFillCall(input, helper);
        }
        else if ("insert".equals(this.type) || "update".equals(this.type) || "delete".equals(this.type))
        {
            return this.genUpdateFillCall(input, helper);
        }
        return null;

    }
}
