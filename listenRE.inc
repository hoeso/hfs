<?php
if( isset($_REQUEST["d"]) )
{
  $a_ = explode( "/", __file__ );
  $b_ = $a_[count($a_)-1];
}
while( $row=mysql_fetch_array( $result, MYSQL_NUM ) )
{
  tabellenZeileBeginnen();
  $fAendern = true;
  foreach( $arrNichtAendern as $k )
    if( 0 == strcmp( $k, $_E['entitaet'] ) )
      $fAendern = false;
    if( $fAendern )
      ausgebenAlsTabellenzeileZumAendern( $row, $auchIDausgeben, $fChecked, $arrFeldTyp, $arrFeldFlag, $arrFeldName, $_E['entitaet'], $ActionSuffix, $iFarbReihe );
    else
    {
      if( !isset($globalID) )
        $globalID=0;
      ausgebenAlsTabellenzeile( $row, $auchIDausgeben, $fChecked, $spaltenName, $globalID, $arrFeldTyp, $_E['entitaet'], $ActionSuffix, "", $dummy );
    }
  tabellenZeileBeenden();
}

tabelleBeenden();
$succ = mysql_free_result( $result );
?>
