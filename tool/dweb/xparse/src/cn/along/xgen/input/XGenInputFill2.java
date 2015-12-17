package cn.along.xgen.input;

import cn.along.xgen.common.IInputFillerIterator;
import cn.along.xgen.common.IInputStructIterator;
import cn.along.xgen.common.IteratorHelper;
import cn.along.xgen.common.StringUtil;
import cn.along.xgen.common.XgenException;
import cn.along.xgen.struct.XGenStruct;
import cn.along.xparse.XparseBase;
import cn.along.xparse.global.XparseGlobal;
import cn.along.xparse.input.XparseInput;
import cn.along.xparse.method.XparseMethod;
import cn.along.xparse.session.XparseSession;
import cn.along.xparse.sql.XparseSql;
import cn.along.xparse.struct.XparseStruct;
import cn.along.xparse.validator.XparseValidator;

/**
 * 针对每一个结构体进行填充类生成
 * 
 * 填充类格式 public class XXFill{ private StructXX $0; private StructXX $1; public
 * XXFill(StructXX $0,StructXX $1){ this.$0 = $0; this.$1 = $1; } public void
 * xx1() throws XXException{
 * 
 * } public void fill(){ this.xx1(); this.xx2(); } }
 * 
 * @author samsung
 *
 */
public class XGenInputFill2
{
	public static String gen(XparseInput input)
	{
		StringBuilder builder = new StringBuilder();
		input.inputStructForEach(builder, new IInputStructIterator(){

			@Override
            public void iterator(XparseInput input, XparseStruct struct,
                    IteratorHelper helper, Object arg)
            {
				StringBuilder builder = (StringBuilder)arg;
	            String ret=XGenStruct.gen(struct);
	            builder.append(ret);
	            
            }}); 
		String ret=XGenInputFill2.gen(input, "TestDemo");
		builder.append(ret);
		return builder.toString();
	}

	public static String gen(XparseInput input, String fill_name)
	{
		StringBuilder builder = new StringBuilder();
		builder.append(XGenInputFill2.genClassHeader(fill_name));
		builder.append("{\n");
		builder.append(XGenInputFill2.genMemberVariable(input));
		builder.append(XGenInputFill2.genClassContructor(input, fill_name));
		builder.append(XGenInputFill2.genFillerMethod(input));
		builder.append("}\n");
		return builder.toString();
	}

	private static String genFillerMethod(XparseInput input)
	{
		StringBuilder builder = new StringBuilder();

		// create fill function
		input.inputFillerForEach(builder, new IInputFillerIterator()
		{

			@Override
			public void iterator(XparseInput input, XparseBase xbase,
					IteratorHelper helper, Object arg)
			{
				StringBuilder builder = (StringBuilder) arg;
				try
				{
					String result = xbase.genFillFunction(input, helper);
					if (result != null)
					{
						builder.append(result);
					}
				}
				catch (XgenException e)
				{
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
			}
		});

		builder.append("\tpublic void filler()\n");
		builder.append("\t{\n");
		input.inputFillerForEach(builder, new IInputFillerIterator()
		{
			@Override
			public void iterator(XparseInput input, XparseBase xbase,
					IteratorHelper helper, Object arg)
			{
				StringBuilder builder = (StringBuilder) arg;
				try
				{
					String result = xbase.genFillCall(input, helper);
					if (result != null)
					{
						builder.append(result);
					}
				}
				catch (XgenException e)
				{
					e.printStackTrace();
				}
			}

		});
		builder.append("\t}\n");
		return builder.toString();
	}

	private static String genMemberVariable(XparseInput input)
	{
		StringBuilder builder = new StringBuilder();
		input.inputStructForEach(builder, new IInputStructIterator()
		{

			@Override
			public void iterator(XparseInput input, XparseStruct struct,
					IteratorHelper helper, Object arg)
			{
				StringBuilder builder = (StringBuilder) arg;
				builder.append("\tprivate "
						+ StringUtil.initialUpper(struct.getType()) + " $"
						+ helper.getElementIndex() + ";\n");

				if (helper.isLastElement())
				{
					builder.append("\n");
				}
			}
		});
		return builder.toString();
	}

	private static String genClassContructor(XparseInput input, String fill_name)
	{
		StringBuilder builder = new StringBuilder();
		builder.append("\tpublic " + StringUtil.initialUpper(fill_name) + "(");
		input.inputStructForEach(builder, new IInputStructIterator()
		{

			@Override
			public void iterator(XparseInput input, XparseStruct struct,
					IteratorHelper helper, Object arg)
			{
				StringBuilder builder = (StringBuilder) arg;
				builder.append(StringUtil.initialUpper(struct.getType()) + " $"
						+ helper.getElementIndex());
				if (!helper.isLastElement())
				{
					builder.append(" , ");
				}
			}

		});
		builder.append(")\n");
		builder.append("\t{\n");
		input.inputStructForEach(builder, new IInputStructIterator()
		{
			@Override
			public void iterator(XparseInput input, XparseStruct struct,
					IteratorHelper helper, Object arg)
			{
				StringBuilder builder = (StringBuilder) arg;
				builder.append("\t\tthis.$" + helper.getElementIndex() + "=$"
						+ helper.getElementIndex() + ";\n");
			}

		});

		builder.append("\t}\n");

		return builder.toString();
	}

	private static String genClassHeader(String fill_name)
	{
		StringBuilder builder = new StringBuilder();
		builder.append("public class " + StringUtil.initialUpper(fill_name)
				+ "\n");
		return builder.toString();
	}
}
