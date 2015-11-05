package cn.along.xgen.common;

import cn.along.xparse.XparseBase;
import cn.along.xparse.input.XparseInput;

public interface IInputFillerIterator
{
	public void iterator(XparseInput input, XparseBase xbase,
			IteratorHelper helper, Object arg);

}
