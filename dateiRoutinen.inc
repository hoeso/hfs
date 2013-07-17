<?php
function schreibenInDatei( $datei, $str )
{
	$name = "./download/$datei.txt";
	$fp = fopen( $name, "w" );
	if( !$fp )
	  return;
	fwrite( $fp, "$str\n" );
	fclose( $fp );
}
function erzeugenExcelTabelle( $datei, $tabKopf, $zeilen, $align )
{
	$name = "./download/$datei.xls";
	$fp = fopen( $name, "w" );
	if( !$fp )
	{
		echo"\n<h4>Das Anlegen der Excel-Mappe '$datei' schlug fehl.<br>";
		echo"\nBitte verst&auml;ndigen Sie Ihren Systemadministrator.</h4>";
		exit;
	}
	$anz = count($tabKopf);
	for( $i=0; $i < $anz; $i++ )
	{
		fwrite( $fp, $tabKopf[ $i ] );
		fwrite( $fp, "\t" );
	}
	fwrite( $fp, "\n" );

	for( $i=0; $i < count($zeilen); )
	{
		for( $j=0; $j < $anz; $j++ )
		{
			fwrite( $fp, $zeilen[ $i++ ] );
			fwrite( $fp, "\t" );
		}
		fwrite( $fp, "\n" );
	}
	fclose( $fp );
	return $name;	
}
?>
