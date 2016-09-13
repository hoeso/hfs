<?php
include ("dateiRoutinen.inc");
include ("anzeigeRoutinen.inc");
include ("dbRoutinen.inc");
include ("zeitRoutinen.inc");
include ("anzeigenTabelle.inc");// enthaelt das Select-Stmt-Array $Select
include "entitySQLAbbrev.prj";

function fuellen( $wert, $len, $fuellZ )
{
   $c = $len - strlen( $wert );
   for( ; $c>0; $c-- )
			if( !isset($str) )
        $str = "$fuellZ";//Nullen voranstellen
			else
        $str .= "$fuellZ";//Nullen voranstellen
	 if( isset($str) )
     $str .= $wert;
	 else
     $str = $wert;
   return $str;
}

// wenn Inhalt ungleich dem Index, dann wurde gefuellt
function habWas( $arr, $start, $ende )
{
  for( $i=$start; $i<=$ende; $i++ )
  {
    if( !isset($arr[$i]) )
      break;
    if( $arr[$i] != $i )
      return true;
  }
  return false;
}

function istForeignKeyName( $feld )
{
	$len = strlen($feld) - 2;
	$str = substr($feld, $len, 2); 
	if( strstr($str, "ID" ) )
	    return true;
	return false;
}
function gibCent2stellig( &$betrag )
{
	$pos = strrpos($betrag,'.');
	if( !$pos )
	    $betrag .=".00";
	else
	{
		$len = strlen($betrag);
		if( $len - $pos == 2 )
			    $betrag .="0";
	}
}
function cent2stelligMachen( $betrag )
{
   $arr=explode(".",$betrag);
   $nachkomma=$arr[1][0];
   $ch=$arr[1][2];
   if( $ch < 5 )
      $nachkomma.=$arr[1][1];
   else
      $nachkomma.=$arr[1][1]+1;
   $betrag="$arr[0].$nachkomma";
}
function gibWert( $row, $arrSpalte, $Spalte, &$attribut )
{
	$i=0;
	foreach( $row as $elem )
	{
		if( $Spalte == $arrSpalte[$i] )
		{
		    $attribut = $elem;
		    break;
		}
		$i++;
	}
}
function abschneidenID( $string )
{
	$len = strlen($string) - 2;
	$str = substr($string, $len, 2); 

	if( strstr($str, "ID" ) )
		return str_replace( "ID", "", $string );
	return "";
}
function wertErhoehen( $row, $arrSpalte, $Spalte, &$sum )
{
	$i=0;
	foreach( $row as $elem )
	{
		if( $Spalte == $arrSpalte[$i] )
		{
		    $sum += $elem;
		    break;
		}
		$i++;
	}
}
function dtUmlaute2Tex( &$strUmlaut )
{
  $strUmlaut=str_replace( "ä", "\"a", $strUmlaut );
  $strUmlaut=str_replace( "Ä", "\"A", $strUmlaut );
  $strUmlaut=str_replace( "ö", "\"o", $strUmlaut );
  $strUmlaut=str_replace( "Ö", "\"O", $strUmlaut );
  $strUmlaut=str_replace( "ü", "\"u", $strUmlaut );
  $strUmlaut=str_replace( "Ü", "\"U", $strUmlaut );
  $strUmlaut=str_replace( "ß", "\"s", $strUmlaut );
// Gaensefuesschen auch noch gleich:
}
function entwertenSonderzeichenTex( &$strSonderzeichen )
{
  $strSonderzeichen=str_replace( "_", "\\_", $strSonderzeichen );
  $strSonderzeichen=str_replace( "$", "\\$", $strSonderzeichen );
  $strSonderzeichen=str_replace( "%", "\\%", $strSonderzeichen );
  $strSonderzeichen=str_replace( "&", "\\&", $strSonderzeichen );
}
/*** diese Funktion stammt von:
 *** https://www.tutorials.de/threads/timestamp-aus-kw-wochentag-und-jahr-bilden.297102/
 ***/
function kalenderwoche($kw, $year) {
    $time = strtotime("4 January " . $year);
    if (date('w', $time) != 1)
        $time = strtotime("last Monday", $time);
    $time = strtotime("+" . ($kw - 1) . " weeks", $time);
   
    return $time;
}
/*** Ausdruecke fuer strtotime():
 ***/
$cfsWochentag = array
( // Index korrespondiert mit Entitaet 'Tag'
  "",
  /*1*/"next monday",
  /*2*/"next tuesday",
  /*3*/"next wednesday",
  /*4*/"next thursday",
  /*5*/"next friday",
  /*6*/"next saturday",
  /*7*/"next sunday"
);
?>
