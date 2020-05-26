<?php
/************ Input **********************************************************
 * $ret        	    : Array mit Inhalten des odt Archives
 * _A[DOMdoc]       : DOM Objekt mit content.xml bzw. styles.xml
 *            	    : aus der Vorlage
 *            	    : 
 *****************************************************************************/
$debug = 0;
if( isset($debug) and $debug )
{
  $str = phpversion();
  echo "<br>PHP $str<br>";
}

$str = $_A['DOMdoc']->nodeValue;
$str2 = $_A['DOMdoc']->textContent;
$str3 = $_A['DOMdoc']->nodeType;
$str4 = $_A['DOMdoc']->nodeName;

if( isset($debug) and $debug )
{
  echo "nodeValue : $str<br>\n";
  echo "textContent : $str2<br>\n";
  echo "nodeType : $str3<br>\n";
  echo "nodeName : $str4<br>\n";
}

$i = 0;
if( "5" <= $versionPHP[0] )
{
  $domNodeList = $_A['DOMdoc']->getElementsByTagName('database-display');
  while( $domNode = $domNodeList->item($i) )
  {
    if( $domNode->attributes )
    {
      if( $domNode2 = $domNode->attributes->getNamedItem("column-name") )
      {
        $node = $_A['DOMdoc']->createTextNode( $arr[$domNode2->nodeValue] );
        $domNode->parentNode->replaceChild( $node, $domNode );
      }
    }
    else  ++$i;
  }
  if( isset($debug) and $debug ) echo "\nAnzahl gefundene DOM-Knoten: $i<br>";
}
if( "5" <= $versionPHP[0] )
  $_A['xmlStream'] = $_A['DOMdoc']->saveXML();
if(isset($debug) and $debug) echo "$_A[xmlStream]<br>";
/************ Output *********************************************************
 * $ret        	    : Array mit Inhalten des odt Archives
 * _A[DOMdoc]       : DOM Objekt mit content.xml bzw. styles.xml
 *            	    : aus der Vorlage
 * _A[xmlStream]    : die veraenderte content.xml bzw. styles.xml
 *            	    : 
 *****************************************************************************/
?>
