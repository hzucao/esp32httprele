void handleIndex(){
String html;

html ="<!DOCTYPE html>";
html +="<html lang='pt-BR'>";
html +="<head>";
html +="<meta charset='UTF-8'>";
html +="<meta name='viewport' content='width=device-width, initial-scale=1.0'>";
html +="<title>Acende Luz</title>";
html +="</head>";
html +="<body>";
html +="<form action='/acende'>";
html +="<fieldset>";
html +="<input type='submit' value='Acende'>";
html +="</fieldset>";
html +="</form>";
html +="<br>";
html +="<form action='/acendeP'>";
html +="<fieldset>";
html +="<input type='submit' value='Piscar'>";
html +="</fieldset>";
html +="</form>";
html +="<br>";
html +="<form action='/acendeTime'>";
html +="<fieldset>";
html +="<label for=''>Tempo em segundos:</label>";
html +="<br>";
html +="<input type='number' name='txtTime' id='txtTimeId'>";
html +="<br>";
html +="<input type='number' name='txtTime' id='txtTimeId'>";
html +="<br>";
html +="<input type='submit' value='Acende tempo'>";
html +="</fieldset>";
html +="</form>";
html +="</body>";
html +="</html>";
server.send(200, "text/html", html);
}