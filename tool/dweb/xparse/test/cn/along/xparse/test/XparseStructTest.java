package cn.along.xparse.test;

import java.io.IOException;
import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;

import javax.xml.parsers.ParserConfigurationException;

import org.w3c.dom.Element;
import org.xml.sax.SAXException;

import cn.along.xparse.XparseBase;

public class XparseStructTest
{
	private static void testCommon(String tagName, String class_name,
			ITestXparseBase testBase)
	{
		Element[] e = null;
		try
		{
			e = LoadFile.load_file(tagName);
		}
		catch (ParserConfigurationException e1)
		{
			e1.printStackTrace();
		}
		catch( IOException e1)
		{
			e1.printStackTrace();
		}
		catch(SAXException e1)
		{
			e1.printStackTrace();
		}

		for (int i = 0; i < e.length; ++i)
		{
				
				try
				{
					Class<?> c;
					c = Class.forName(class_name);
					Method method = c.getMethod("parse", Element.class);
					XparseBase out = (XparseBase) method.invoke(null, e[i]);
					// System.out.println(out.createString());
					testBase.test(out);
				}
				catch (ClassNotFoundException e1)
				{
					// TODO Auto-generated catch block
					e1.printStackTrace();
				}
				catch (NoSuchMethodException e1)
				{
					// TODO Auto-generated catch block
					e1.printStackTrace();
				}
				catch (SecurityException e1)
				{
					e1.printStackTrace();
				}
				catch (IllegalAccessException e1)
				{
					e1.printStackTrace();
				}
				catch (IllegalArgumentException e1)
				{
					e1.printStackTrace();
				}
				catch (InvocationTargetException e1)
				{
					e1.printStackTrace();
				}
				
		
		}

	}

	public static void testGen(String tagName, String parse_class,
			String gen_class)
	{
		class TestGen implements ITestXparseBase
		{
			private String gen_class;
			private String parse_class;

			public TestGen(String parse_class, String gen_class)
			{
				this.gen_class = gen_class;
				this.parse_class = parse_class;
			}

			@Override
			public void test(XparseBase base)
			{
				try
				{
					Class<?> c = Class.forName(gen_class);
					Class<?> parse = Class.forName(parse_class);
					Method method = c.getMethod("gen", parse);
					String out = (String) method.invoke(null, base);
					System.out.println(out);
				}
				catch (ClassNotFoundException  e)
				{
					e.printStackTrace();
				}
				catch (NoSuchMethodException e)
				{
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
				catch (SecurityException e)
				{
					e.printStackTrace();
				}
				catch (IllegalAccessException e)
				{
					e.printStackTrace();
				}
				catch (IllegalArgumentException e)
				{
					e.printStackTrace();
				}
				catch (InvocationTargetException e)
				{
					e.printStackTrace();
				}

			}

		}
		XparseStructTest.testCommon(tagName, parse_class, new TestGen(
				parse_class, gen_class));

	}

	public static void testParse(String tagName, String class_name)
	{
		XparseStructTest.testCommon(tagName, class_name, new ITestXparseBase()
		{

			@Override
			public void test(XparseBase base)
			{
				System.out.println(base.createString());
			}
		});
	}

	/**
	 * public static void testStructParse() { Element[] e = null; try { e =
	 * LoadFile.load_file("struct"); } catch (ParserConfigurationException |
	 * SAXException | IOException e1) { e1.printStackTrace(); }
	 * 
	 * for (int i = 0; i < e.length; ++i) { try { XparseStruct struct =
	 * XparseStruct.parse(e[i]); System.out.println(struct.toString());
	 * 
	 * } catch (XparseSyntaxException e1) { e1.printStackTrace(); } } }
	 * 
	 * public static void testInputParse() { Element[] e = null; try { e =
	 * LoadFile.load_file("input"); } catch (ParserConfigurationException |
	 * SAXException | IOException e1) { e1.printStackTrace(); }
	 * 
	 * for (int i = 0; i < e.length; ++i) { try { XparseInput input =
	 * XparseInput.parse(e[i]); System.out.println(input.toString());
	 * 
	 * } catch (XparseSyntaxException e1) { e1.printStackTrace(); } }
	 * 
	 * }
	 */
	public static void main(String[] args)
	{
		// XparseStructTest.testStructParse();
		// XparseStructTest.testInputParse();
		XparseStructTest.testParse("struct",
				"cn.along.xparse.struct.XparseStruct");
		XparseStructTest.testGen("struct",
				"cn.along.xparse.struct.XparseStruct",
				"cn.along.xgen.struct.XGenStruct");
		XparseStructTest
				.testParse("input", "cn.along.xparse.input.XparseInput");
		XparseStructTest.testGen("input", "cn.along.xparse.input.XparseInput",
				"cn.along.xgen.input.XGenInputFill");
		XparseStructTest
				.testParse("state", "cn.along.xparse.state.XparseState");

	}
}
