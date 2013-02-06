<?
/************ Input **********************************************************
 * zielTabelle	    : in die zu speichernde Tabelle
 * keinInsert	    : es wird kein Datensatz angeboten zum Erfassen
 * $_POST     	    : NEU seit PHP 5, es gibt kein $HTTP_POST_VARS mehr
 *****************************************************************************/
$debug = false;
$HTTP_POST_VARS = $_POST;
reset( $HTTP_POST_VARS );

foreach( $HTTP_POST_VARS as $k=>$elem )
{
	if( $debug )
	    echo"\nk : $k, elem: $elem<br>";
	switch( $k )
	{
		case "PK":
		     $PK = $elem;
		     break;
		case "SL1":
		     $SL1 = $elem;
		     break;
		case "SL2":
		     $SL2 = $elem;
		     break;
		case "SL3":
		     $SL3 = $elem;
		     break;
		case "SL4":
		     $SL4 = $elem;
		     break;
		case "SL5":
		     $SL5 = $elem;
		     break;
		case "MULTI1SL1":
		     $MULTI1SL1 = $elem;
		     break;
	}
}
if( isset($debugPK) and $debugPK )
    echo"\nPK = $PK. globalID = $globalID. TabellePK=$TabellePK<br>";
if( $debug )
{
	echo "\nAnzahl RE-Tabellen: $countRE<br>";
	echo "\nAnzahl MM-Tabellen: $countMM<br>";
	echo "\nAnzahl EM-Tabellen: $countEM<br>";
	echo "\nAnzahl SL-Tabellen: $countSL<br>";
	echo "\nAnzahl MULTISL-Tabellen: $countMULTISL<br>";
}
$i=0;
// zugegebenermassen eine bloede Methode, um GET-Variablen ueber einen
// counter auszulesen. Doch ich weiss noch keine bessere
if( !isset($countRE) )
  $countRE=0;
if( $i < $countRE )
{
	$arrRE[ $i ] = $tableRE1;
	$labelRE[ $i++ ] = "RE1";
	if( $debug )
	    echo "\n$tableRE1<br>";
}
if( $i < $countRE )
{
	$arrRE[ $i ] = $tableRE2;
	$labelRE[ $i++ ] = "RE2";
	if( $debug )
	    echo "\n$tableRE2<br>";
}
if( $i < $countRE )
{
	$arrRE[ $i ] = $tableRE3;
	$labelRE[ $i++ ] = "RE3";
	if( $debug )
	    echo "\n$tableRE3<br>";
}
if( $i < $countRE )
{
	$arrRE[ $i ] = $tableRE4;
	$labelRE[ $i++ ] = "RE4";
	if( $debug )
	    echo "\n$tableRE4<br>";
}
if( $i < $countRE )
{
	$arrRE[ $i ] = $tableRE5;
	$labelRE[ $i++ ] = "RE5";
	if( $debug )
	    echo "\n$tableRE5<br>";
}
if( $i < $countRE )
{
	echo "\nModul formularERMintro.inc hat nicht mehr als 5 Tabellen vorgesehen. Die Zahl muss dort erhoeht	werden.<br>";
	echo "Verst&auml;ndigen Sie Ihren Systemadministrator.<br>";
	exit;
}
$i = 0;
if( !isset($countEM) )
  $countEM=0;
if( $i < $countEM )
{
	$arrEM[ $i ] = $tableEM1;
	$labelEM[ $i++ ] = "EM1";
	if( $debug )
	    echo "\n$tableEM1<br>";
}
if( $i < $countEM )
{
	$arrEM[ $i ] = $tableEM2;
	$labelEM[ $i++ ] = "EM2";
	if( $debug )
	    echo "\n$tableEM2<br>";
}
if( $i < $countEM )
{
	$arrEM[ $i ] = $tableEM3;
	$labelEM[ $i++ ] = "EM3";
	if( $debug )
	    echo "\n$tableEM3<br>";
}
if( $i < $countEM )
{
	echo "\nModul formularERMintro.inc hat nicht mehr als 3 1:M-Tabellen vorgesehen. Die Zahl muss dort erhoeht werden.<br>";
	echo "Verst&auml;ndigen Sie Ihren Systemadministrator.<br>";
	exit;
}
$i = 0;
unset($arrSL);
if( !isset($countSL) )
  $countSL=0;
if( $i < $countSL )
{
  if( $debug) echo"\n$SL1<br>";
        if( isset($hrefSL1) )
	  $arrSL[ $i ] = "<A HREF=\"$hrefSL1\">$tableSL1</A>";
	else
	  $arrSL[ $i ] = $tableSL1;
	if(!strcmp("anzeigenTabelle",$SL1))
		$SL1="select * from Sonderleistung";
	$SL1=str_replace( "\'", "'", $SL1 );
	$SL1=str_replace( "|", " ", $SL1 );
	$SL1=str_replace( "&uuml;", "ü", $SL1 );
	if( isset($globalID) )
	  $SL1=str_replace( "\$globalID", $globalID, $SL1 );
	if( isset($gNLID) )
	  $SL1=str_replace( "\$gNLID", $gNLID, $SL1 );
	if( isset($SELECTSL1) )
	  $SL1=str_replace( "\$SELECTSL1", $SELECTSL1, $SL1 );
	if( isset($gPaketID) )
	  $SL1=str_replace( "\$gPaketID", $gPaketID, $SL1 );
//echo"\n<!-- $SL1 --><br>";
	$SL[ $i ] = $SL1;
	$labelSL[ $i++ ] = "SL1";
	if( $debug )
	    echo "\ntableSL1 : $tableSL1; SL1 : $SL1<br>";
}
if( $i < $countSL )
{
	$arrSL[ $i ] = $tableSL2;
	$SL2=str_replace( "\'", "'", $SL2 );
	$SL2=str_replace( "|", " ", $SL2 );
	$SL2=str_replace( "&uuml;", "ü", $SL2 );
	if( isset($globalID) )
	  $SL2=str_replace( "\$globalID", $globalID, $SL2 );
	if( isset($SELECTSL1) )
	  $SL2=str_replace( "\$SELECTSL1", $SELECTSL1, $SL2 );
	$SL2=str_replace( "\$gPaketID", $gPaketID, $SL2 );
	$SL[ $i ] = $SL2;
	$labelSL[ $i++ ] = "SL2";
	if( $debug )
	    echo "\n$tableSL2<br>";
}
if( $i < $countSL )
{
	$arrSL[ $i ] = $tableSL3;
	$SL3=str_replace( "\'", "'", $SL3 );
	$SL3=str_replace( "&uuml;", "ü", $SL3 );
	if( isset($globalID) )
	  $SL3=str_replace( "\$globalID", $globalID, $SL3 );
	$SL[ $i ] = $SL3;
	$labelSL[ $i++ ] = "SL3";
	if( $debug )
	    echo "\n$tableSL3<br>";
}
if( $i < $countSL )
{
	$arrSL[ $i ] = $tableSL4;
	$SL4=str_replace( "\'", "'", $SL4 );
	$SL4=str_replace( "&uuml;", "ü", $SL4 );
	if( isset($globalID) )
	  $SL4=str_replace( "\$globalID", $globalID, $SL4 );
	$SL[ $i ] = $SL4;
	$labelSL[ $i++ ] = "SL4";
	if( $debug )
	    echo "\n$tableSL4<br>";
}
if( $i < $countSL )
{
	echo "\nModul formularERMintro.inc hat nicht mehr als 4 SL-Tabellen vorgesehen. Die Zahl muss dort erhoeht werden.<br>";
	echo "Verst&auml;ndigen Sie Ihren Systemadministrator.<br>";
	exit;
}
if( isset($countMULTISL) )
  include("multiSLIntro.inc");
if( !isset($countMM) )
  $countMM=0;
$i = 0;
if( $i < $countMM )
{
	$arrMM[ $i ] = $tableMM1;
	$labelMM[ $i++ ] = "MM1";
	if( $debug )
	    echo "\n$tableMM1<br>";
}
if( $i < $countMM )
{
	$arrMM[ $i ] = $tableMM2;
	$labelMM[ $i++ ] = "MM2";
	if( $debug )
	    echo "\n$tableMM2<br>";
}
if( $i < $countMM )
{
	$arrMM[ $i ] = $tableMM3;
	$labelMM[ $i++ ] = "MM3";
	if( $debug )
	    echo "\n$tableMM3<br>";
}
if( $i < $countMM )
{
	echo "\nModul formularERMintro.inc hat nicht mehr als 3 JE-Tabellen vorgesehen. Die Zahl muss dort erhoeht werden.<br>";
	echo "Verst&auml;ndigen Sie Ihren Systemadministrator.<br>";
	exit;
}
if( $_E['entitaet'] )
    $arrMM[ $i++ ] = $_E['entitaet'];

if( isset($TabellePK) and $TabellePK )	// Den  Datensatz anzeigen, fuer den zugeordnet wird
{
	if( true==$SelNurPK )
	    $sql_ = $SelectNurPK[$TabellePK];
	else
		$sql_ = $Select[$TabellePK];
	if( !$PK )
	    $PK=$globalID;
    $sql_ .= " and " . $TabellePK . ".ID=$PK";
    anzeigen( $MySQLDb, $sql_, $_E['entitaet'], "" );
}

// *** Plausi: is ueberhaupt schon ein Datensatz angelegt?
if( isset($BOGesID) and $BOGesID and isset($keinInsert) and $keinInsert )
{
  $praefix = gibFeld( $MySQLDb, "SELECT KontoPraefix FROM KontoSicherheitseinbehalt WHERE GesellschaftID=$BOGesID", 0 );
  if( !$praefix )
    unset( $keinInsert );
  unset( $praefix );
}
if( !isset($keinInsert) or false == $keinInsert )
{
  ?><table>
  <tr><?
  if( isset($arrSL) )
    for( $i=0; $i<count($arrSL); $i++ )
    {
	  ?><th><?
	  echo $arrSL[$i];
	  ?></th><?
    }

  if( isset($arrMULTISL) )
    for( $i=0; $i<count($arrMULTISL); $i++ )
    {
	  ?><th><?
	  echo $arrMULTISL[$i];
	  ?></th><?
    }
  if( isset($arrRE) )
    for( $i=0; $i<count($arrRE); $i++ )
    {
	  ?><th><?
	  $str=$arrRE[ $i ];
	  $str=str_replace( "ae", "&auml;", $str );
	  echo $str;
	  ?></th><?
    }
  if( isset($arrEM) )
    for( $i=0; $i<count($arrEM); $i++ )
    {
	  ?><th><?
	  echo $arrEM[$i];
	  ?></th><?
    }
  if( isset($arrMM) )
    for( $i=0; $i<count($arrMM); $i++ )
    {
	  ?><th><?
	  echo $arrMM[$i];
	  ?></th><?
    }
  if( !$_E['entitaet'] )	// der weiter... - Knopf soll noch rechts der Liste erscheinen
  {
    ?><th></th><?
  }
  // 29.1.04: Der Speichern-Knopf soll im Fall von $_E['entitaet'] nicht mehr in einer eigenen Spalte hinter den Eingabefelder sein
  echo "\n</tr>";
  if( $_E['entitaet'] )
    echo "\n\t<input type='hidden' name='zielTabelle' value='{$_E['entitaet']}'>";
}
?>
