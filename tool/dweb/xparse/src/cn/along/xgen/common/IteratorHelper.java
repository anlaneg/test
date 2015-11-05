package cn.along.xgen.common;

public class IteratorHelper
{
	private boolean first;
	private boolean last;
	private int idx;
	private int size;

	public IteratorHelper(boolean first, boolean last, int idx, int size)
	{
		this.first = first;
		this.last = last;
		this.idx = idx;
		this.size = size;
	}

	public boolean isFirstElement()
	{
		return first;
	}

	public boolean isLastElement()
	{
		return last;
	}

	public int getElementIndex()
	{
		return idx;
	}

	public int getElementTotalSize()
	{
		return size;
	}
}
