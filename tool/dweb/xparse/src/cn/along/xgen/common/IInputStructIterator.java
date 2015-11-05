package cn.along.xgen.common;

import cn.along.xparse.input.XparseInput;
import cn.along.xparse.struct.XparseStruct;

public interface IInputStructIterator
{
	public void iterator(XparseInput input, XparseStruct struct,IteratorHelper helper, Object arg);
}
