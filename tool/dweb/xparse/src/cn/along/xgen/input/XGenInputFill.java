package cn.along.xgen.input;

import cn.along.xgen.common.IInputFillerIterator;
import cn.along.xgen.common.IInputStructIterator;
import cn.along.xgen.common.IteratorHelper;
import cn.along.xgen.common.StringUtil;
import cn.along.xgen.common.XgenException;
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
 * 填充类格式
 * public class XXFill{
 * 		private StructXX $0;
 * 		private StructXX $1;
 * 		public XXFill(StructXX $0,StructXX $1){
 * 			this.$0 = $0;
 * 			this.$1 = $1;
 * 		}
 * 		public void xx1() throws XXException{
 * 			
 * 		}
 * 		public void fill(){
 * 			this.xx1();
 * 			this.xx2();
 * 		} 
 * }
 * @author samsung
 *
 */
public class XGenInputFill
{
	public static String gen(XparseInput input)
	{
		return XGenInputFill.gen(input, "TestDemo");
	}

	public static String gen(XparseInput input, String fill_name)
	{
		StringBuilder builder = new StringBuilder();
		builder.append(XGenInputFill.genClassHeader(fill_name));
		builder.append("{\n");
		builder.append(XGenInputFill.genMemberVariable(input));
		builder.append(XGenInputFill.genClassContructor(input, fill_name));
		builder.append(XGenInputFill.genFillerMethod(input));
		builder.append("}\n");
		return builder.toString();
	}

	private static String genFillerMethod(XparseInput input)
	{
		StringBuilder builder = new StringBuilder();
		
		//create fill function
		input.inputFillerForEach(builder, new IInputFillerIterator()
		{

			@Override
			public void iterator(XparseInput input, XparseBase xbase,
					IteratorHelper helper, Object arg)
			{
				StringBuilder builder = (StringBuilder) arg;
				if (xbase instanceof XparseSql)
				{
					try
					{
						XGenInputFill.genSqlFillFunction(input, (XparseSql) xbase, helper,
								builder);
					}
					catch (XgenException e)
					{
						// TODO Auto-generated catch block
						e.printStackTrace();
					}
				}
				else if (xbase instanceof XparseMethod)
				{
					XGenInputFill.genMethodFillFunction(input, (XparseMethod) xbase,
							helper, builder);
				}
				else if (xbase instanceof XparseValidator)
				{
					XGenInputFill.genValidatorCheckFunction(input,
							(XparseValidator) xbase, helper, builder);
				}
				else if (xbase instanceof XparseSession)
				{
					XGenInputFill.genSessionFillFunction(input, (XparseSession) xbase,
							helper, builder);
				}
				else if (xbase instanceof XparseGlobal)
				{
					XGenInputFill.genGlobalFillFunction(input, (XparseGlobal) xbase,
							helper, builder);
				}
				else
				{
					throw new RuntimeException(
							"Unkown instance ,class name is :"
									+ xbase.getClass().getName());
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
				if (xbase instanceof XparseSql)
				{
					XGenInputFill.genSqlFill(input, (XparseSql) xbase, helper,
							builder);
				}
				else if (xbase instanceof XparseMethod)
				{
					XGenInputFill.genMethodFill(input, (XparseMethod) xbase,
							helper, builder);
				}
				else if (xbase instanceof XparseValidator)
				{
					XGenInputFill.genValidatorCheck(input,
							(XparseValidator) xbase, helper, builder);
				}
				else if (xbase instanceof XparseSession)
				{
					XGenInputFill.genSessionFill(input, (XparseSession) xbase,
							helper, builder);
				}
				else if (xbase instanceof XparseGlobal)
				{
					XGenInputFill.genGlobalFill(input, (XparseGlobal) xbase,
							helper, builder);
				}
				else
				{
					throw new RuntimeException(
							"Unkown instance ,class name is :"
									+ xbase.getClass().getName());
				}
			}

		});
		builder.append("\t}\n");
		return builder.toString();
	}

	protected static void genGlobalFillFunction(XparseInput input,
			XparseGlobal xbase, IteratorHelper helper, StringBuilder builder)
	{
		// TODO Auto-generated method stub
		
	}

	protected static void genSessionFillFunction(XparseInput input,
			XparseSession xbase, IteratorHelper helper, StringBuilder builder)
	{
		// TODO Auto-generated method stub
		
	}

	protected static void genValidatorCheckFunction(XparseInput input,
			XparseValidator xbase, IteratorHelper helper, StringBuilder builder)
	{
		// TODO Auto-generated method stub
		
	}

	protected static void genMethodFillFunction(XparseInput input,
			XparseMethod xbase, IteratorHelper helper, StringBuilder builder)
	{
		// TODO Auto-generated method stub
		
	}

	protected static void genSqlFillFunction(XparseInput input,
			XparseSql xbase, IteratorHelper helper, StringBuilder builder) throws XgenException
	{
			builder.append(xbase.createSqlLoadFunction(input));
	}

	protected static void genGlobalFill(XparseInput input, XparseGlobal xbase,
			IteratorHelper helper, StringBuilder builder)
	{

	}

	protected static void genSessionFill(XparseInput input,
			XparseSession xbase, IteratorHelper helper, StringBuilder builder)
	{

	}

	protected static void genValidatorCheck(XparseInput input,
			XparseValidator xbase, IteratorHelper helper, StringBuilder builder)
	{

	}

	protected static void genMethodFill(XparseInput input, XparseMethod xbase,
			IteratorHelper helper, StringBuilder builder)
	{

	}

	protected static void genSqlFill(XparseInput input, XparseSql xbase,
			IteratorHelper helper, StringBuilder builder)
	{
		try
		{
			builder.append(xbase.createSqlParameter("abc",input));
		}
		catch (XgenException e)
		{
			e.printStackTrace();
		}
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
