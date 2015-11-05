package cn.along.xgen.common;

import cn.along.xparse.struct.XparseStruct;
import cn.along.xparse.struct.XparseStructMember;

public interface IStructMemberIterator
{
	public void iterator(XparseStruct struct,XparseStructMember member,Object arg);
}
