<?php
function echo_( $str )
{
	global $fAnzeigeUnterdruecken;
	if( $fAnzeigeUnterdruecken )
	   return;
	global $teeFile;
	echo( $str );
	if( $teeFile )
	    anhaengenAnDatei( $teeFile, $str );
}
function anhaengenAnDatei( $datei, $str )
{
	global $aName;
	global $aFp;
	if( !$aName[$datei] )
	{
		$aName[$datei] = $datei;
		$aFp[$datei] = fopen( $aName[$datei], "w+" );
	}		
	else
		$aFp[$datei] = fopen( $aName[$datei], "a" );
	if( !$aFp[$datei] )
	    return;

	fwrite( $aFp[$datei], $str );
	fclose( $aFp[$datei] );
}
?>
