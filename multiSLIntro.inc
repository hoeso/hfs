<?php
$i = 0;
if( !isset($countMULTISL) )
  $countMULTISL=0;
if( $i < $countMULTISL )
{
	$arrMULTISL[ $i ] = $tableMULTI1SL;
	$j=0;
	if( $j < $countMULTI1SL )
	{
		$arrMULTI1SL[$i][ $j ] = $tableMULTI1SL;
		$MULTI1SL1=str_replace( "\'", "'", $MULTI1SL1 );
		$MULTI1SL1=str_replace( "&uuml;", "ü", $MULTI1SL1 );
		$MULTI1SL[$i][ $j ] = $MULTI1SL1;
		$labelMULTI1SL[$i][ $j++ ] = "SL1";

		if( $debug )
		    echo "\nMULTI1tableSL : $tableMULTI1SL; MULTI1SL1 : $MULTI1SL1<br>";
	}
	if( $j < $countMULTI1SL )
	{
		$arrMULTI1SL[$i][ $j ] = $tableMULTI1SL;
		$MULTI1SL2=str_replace( "\'", "'", $MULTI1SL2 );
		$MULTI1SL2=str_replace( "&uuml;", "ü", $MULTI1SL2 );
		$MULTI1SL[$i][ $j ] = $MULTI1SL2;
		$labelMULTI1SL[$i][ $j++ ] = "SL1";

		if( $debug )
		    echo "\nMULTI1tableSL : $tableMULTI1SL; MULTI1SL2 : $MULTI1SL2<br>";
	}
	if( $j < $countMULTI1SL )
	{
		$arrMULTI1SL[$i][ $j ] = $tableMULTI1SL;
		$MULTI1SL3=str_replace( "\'", "'", $MULTI1SL3 );
		$MULTI1SL3=str_replace( "&uuml;", "ü", $MULTI1SL3 );
		$MULTI1SL[$i][ $j ] = $MULTI1SL3;
		$labelMULTI1SL[$i][ $j++ ] = "SL1";

		if( $debug )
		    echo "\nMULTI1tableSL : $tableMULTI1SL; MULTI1SL3 : $MULTI1SL3<br>";
	}
	if( $j < $countMULTI1SL )
	{
		$arrMULTI1SL[$i][ $j ] = $tableMULTI1SL;
		$MULTI1SL4=str_replace( "\'", "'", $MULTI1SL4 );
		$MULTI1SL4=str_replace( "&uuml;", "ü", $MULTI1SL4 );
		$MULTI1SL[$i][ $j ] = $MULTI1SL4;
		$labelMULTI1SL[$i][ $j++ ] = "SL1";

		if( $debug )
		    echo "\nMULTI1tableSL : $tableMULTI1SL; MULTI1SL4 : $MULTI1SL4<br>";
	}
	if( $j < $countMULTI1SL )
	{
		$arrMULTI1SL[$i][ $j ] = $tableMULTI1SL;
		$MULTI1SL5=str_replace( "\'", "'", $MULTI1SL5 );
		$MULTI1SL5=str_replace( "&uuml;", "ü", $MULTI1SL5 );
		$MULTI1SL[$i][ $j ] = $MULTI1SL5;
		$labelMULTI1SL[$i][ $j++ ] = "SL1";

		if( $debug )
		    echo "\nMULTI1tableSL : $tableMULTI1SL; MULTI1SL5 : $MULTI1SL5<br>";
	}
	if( $j < $countMULTI1SL )
	{
		echo "\nModul formularERMintro.inc hat nicht mehr als 5 MULTI1SL-Statements vorgesehen. Die Zahl muss dort erhoeht werden.<br>";
		echo "Verst&auml;ndigen Sie Ihren Systemadministrator.<br>";
		exit;
	}
	$i++;
}
if( $i < $countMULTISL )
{
	echo "\nModul formularERMintro.inc hat nicht mehr als 1 MULTISL-Tabellen vorgesehen. Die Zahl muss dort erhoeht werden.<br>";
	echo "Verst&auml;ndigen Sie Ihren Systemadministrator.<br>";
	exit;
}
?>
