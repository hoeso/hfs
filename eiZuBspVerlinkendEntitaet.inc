<?
/************ ERICA MIT mn ***************************************************
 * 
 *****************************************************************************/
if( isset($_E['entitaet']) )
  $zielTabelle = $_E['entitaet'];

if( isset($_E["re"]) )
{
  $countRE = $_E["re"];
  for( $i=1; $i <= $_E['re'] and $i < 6; $i++ )
  {
    if( 1 == $i )
      $tableRE1 = $_E["re$i"];
    else if( 2 == $i )
      $tableRE2 = $_E["re$i"];
    else if( 3 == $i )
      $tableRE3 = $_E["re$i"];
    else if( 4 == $i )
      $tableRE4 = $_E["re$i"];
    else if( 5 == $i )
      $tableRE5 = $_E["re$i"];
  }
}
if( isset($_E["nn"]) )
{
  $countMM = $_E["nn"];
  for( $i=1; $i <= $_E['nn'] and $i < 6; $i++ )
  {
    if( 1 == $i )
      $tableMM1 = $_E["nn$i"];
    else if( 2 == $i )
      $tableMM2 = $_E["nn$i"];
    else if( 3 == $i )
      $tableMM3 = $_E["nn$i"];
    else if( 4 == $i )
      $tableMM4 = $_E["nn$i"];
    else if( 5 == $i )
      $tableMM5 = $_E["nn$i"];
  }
}
?>
