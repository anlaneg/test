package cn.along.xgen.struct;

import cn.along.xgen.common.IStructMemberIterator;
import cn.along.xgen.common.StringUtil;
import cn.along.xparse.struct.XparseStruct;
import cn.along.xparse.struct.XparseStructMember;

public class XGenStruct
{
	public static String gen(XparseStruct struct)
	{
		StringBuilder builder = new StringBuilder();
		builder.append(XGenStruct.genClassHeader(struct));
		builder.append("{\n");
		builder.append(XGenStruct.genMemberVariable(struct));
		builder.append(XGenStruct.genClassContructor(struct));
		builder.append(XGenStruct.genMemberMethod(struct));
		builder.append("}\n");
		return builder.toString();
	}

	private static String genClassHeader(XparseStruct struct)
	{
		StringBuilder builder = new StringBuilder();
		builder.append("public class "
				+ StringUtil.initialUpper(struct.getType()) + "\n");
		return builder.toString();
	}

	private static String genClassContructor(XparseStruct struct)
	{
		StringBuilder builder = new StringBuilder();
		builder.append("public " + StringUtil.initialUpper(struct.getType())
				+ "()\n");
		builder.append("{\n");
		builder.append("//set member default value\n");
		struct.structMemberForEach(builder, new IStructMemberIterator()
		{

			@Override
			public void iterator(XparseStruct struct,
					XparseStructMember member, Object arg)
			{
				StringBuilder builder = (StringBuilder) arg;
				builder.append("this." + member.getVariableName() + "=" + member.getContructor() + "\n");
			}
		});		
		builder.append("}\n\n");
		return builder.toString();
	}

	private static String genMemberVariable(XparseStruct struct)
	{
		StringBuilder builder = new StringBuilder();
		struct.structMemberForEach(builder, new IStructMemberIterator()
		{

			@Override
			public void iterator(XparseStruct struct,
					XparseStructMember member, Object arg)
			{
				StringBuilder builder = (StringBuilder) arg;
				builder.append("// " + member.getComment().replaceAll("\n", " ") + "\n");
				builder.append("private " + member.getType() + " "
						+ member.getVariableName() + ";\n\n");
			}
		});

		return builder.toString();
	}

	private static String genMemberMethod(XparseStruct struct)
	{
		StringBuilder builder = new StringBuilder();
		struct.structMemberForEach(builder, new IStructMemberIterator()
		{

			@Override
			public void iterator(XparseStruct struct,
					XparseStructMember member, Object arg)
			{
				StringBuilder builder = (StringBuilder) arg;
				builder.append("//set " + member.getVariableName() + ":" + member.getComment().replaceAll("\n", " ") + "\n");
				builder.append("public void set"
						+ StringUtil.initialUpper(member.getVariableName())
						+ "(" + member.getType() + " "
						+ member.getVariableName() + ")\n");
				builder.append("{\n");
				builder.append("this." + member.getVariableName() + "="
						+ member.getVariableName() + ";\n");
				builder.append("}\n\n");

				builder.append("//get " + member.getVariableName() + ":" + member.getComment().replaceAll("\n", " ") + "\n");
				builder.append("public " + member.getType() + " get"
						+ StringUtil.initialUpper(member.getVariableName())
						+ "()\n");
				builder.append("{\n");
				builder.append("return this." + member.getVariableName()
						+ ";\n");
				builder.append("}\n\n");

			}
		});

		return builder.toString();
	}
}
