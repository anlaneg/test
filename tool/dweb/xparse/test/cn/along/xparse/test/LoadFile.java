package cn.along.xparse.test;

import java.io.File;
import java.io.FilenameFilter;
import java.io.IOException;

import javax.xml.parsers.DocumentBuilder;
import javax.xml.parsers.DocumentBuilderFactory;
import javax.xml.parsers.ParserConfigurationException;

import org.w3c.dom.Document;
import org.w3c.dom.Element;
import org.xml.sax.SAXException;

import cn.along.xparse.common.Assert;

public class LoadFile
{
	public static String parent_path = "/home/samsung/project/jworkspace/xparse/res";

	public static Element[] load_file(final String name)
			throws ParserConfigurationException, SAXException, IOException
	{
		File f = new File(parent_path);
		Assert.test(f.isDirectory());
		String[] files_name = f.list(new FilenameFilter()
		{
			public boolean accept(java.io.File dir, java.lang.String file_name)
			{
				if (file_name.startsWith(name))
				{
					return true;
				}
				return false;
			}
		});

		Element[] element = new Element[files_name.length];
		for (int i = 0; i < files_name.length; ++i)
		{
			System.out.println(files_name[i]);
			Document document = null;
			DocumentBuilderFactory builderFactory = DocumentBuilderFactory
					.newInstance();
			DocumentBuilder builder = builderFactory.newDocumentBuilder();
			document = builder.parse(new File(parent_path, files_name[i]));

			element[i] = document.getDocumentElement();
		}
		return element;
	}
}
