<?php
function gibTagesDiff( $datum )
{
   global $MySQLDb;

   $heute = gibFeld( $MySQLDb, "SELECT NOW()", 0 );
   $arr=explode( " ", $heute );
   $heute=$arr[0];
   $ar=explode( "-", $arr[0] );
   $diesesMonat=$ar[0].$ar[1];
   $ar=explode( "-", $datum );

   $datumMonat=$ar[0].$ar[1];

   if( $heute > $datum )
      $diff = gibFeld( $MySQLDb, "SELECT PERIOD_DIFF($diesesMonat,$datumMonat)", 0 );
   else
      $diff = gibFeld( $MySQLDb, "SELECT PERIOD_DIFF($datumMonat,$diesesMonat)", 0 );
   if( isset($debug) and $debug )
   {echo"$heute:heute $datum:datum $diesesMonat:diesesMonat $datumMonat:datumMonat $diff:diffMonate<br>";exit;}
   return $diff;   
}
?>
