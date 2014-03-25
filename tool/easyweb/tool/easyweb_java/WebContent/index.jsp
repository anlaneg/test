<%@ page language="java" contentType="text/html; charset=UTF-8"
	pageEncoding="UTF-8"%>
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
<title>Test input</title>
</head>
<body>
	<form method="post" action="/easyweb/action.do">
		<textarea id="hello" name="hello" rows="10">{ "head":{ "version":1,"encode":"utf-8","name":["cn.along.easyweb.core.flowframe.test.Login",] },"content":[{"name":"along","password":"hello"},],"extend":null}</textarea>
		<input type="submit" value="submit" />
	</form>
</body>
</html>