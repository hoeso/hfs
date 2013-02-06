<?
/************ ERICA MIT mn ***************************************************
 * 
 *****************************************************************************/
if( isset($_E['entitaet']) && isset($_E['entitaet1N']) )
{ 
  $countEM = 1;
  $tableEM1 = $_E['entitaet1N'];
  $zielTabelle = $_E['entitaet'];
}
if( isset($_E['nSpaltenGruppieren']) )
  $gruppenStaerke = $_E['nSpaltenGruppieren'];
if( isset($_E['nichtEinfuegen']) )
  $keinInsert = $_E['nichtEinfuegen'];
?>
