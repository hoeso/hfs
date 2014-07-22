<?php
$url = 'https://maps.googleapis.com/maps/api/geocode/xml?address=pupplinger+weg+2,+82544+egling&sensor=false';
$handle = curl_init($url);
curl_setopt($handle,  CURLOPT_RETURNTRANSFER, TRUE);

/* Get the HTML or whatever is linked in $url. */
$response = curl_exec($handle);

/* Check for 404 (file not found). */
$httpCode = curl_getinfo($handle, CURLINFO_HTTP_CODE);

//echo $httpCode;

//echo $response;

curl_close($handle);

if( 200 <> $httpCode )
{
  $wZu="fortsetzend";
  include("forkZu.inc");
}
$xml = simplexml_load_string($response);
$json = json_encode($xml);
$vek = json_decode($json,TRUE);

    foreach( $arrAttr as $k=>$elem )
    {
      //echo "\nAttr: $k -- $elem<br>";
    }
//echo $vek['status'] . "<p>";
//echo $vek['result'] . "<p>";
if( 'OK' == $vek['status'] )
{
  /***
  foreach( $vek['result'] as $k=>$e )
  {
    echo "\n$k -- $e<br>";
  }
  echo "\naddress_component:<br>";
  foreach( $vek['result']['address_component'] as $k=>$e )
  {
    echo "\n$k -- $e<br>";
  }
  echo "\ngeometry:<br>";
  foreach( $vek['result']['geometry'] as $k=>$e )
  {
    echo "\n$k -- $e<br>";
  }
  echo "\ngeometry - location:<br>";
  foreach( $vek['result']['geometry']['location'] as $k=>$e )
  {
    echo "\n$k -- $e<br>";
  }
   ***/
  echo "\nlocation type = " . $vek['result']['geometry']['location_type'] . "<br>";
  echo "\nlat = " . $vek['result']['geometry']['location']['lat'] . "<br>";
  echo "\nlng = " . $vek['result']['geometry']['location']['lng'] . "<br>";
}
?>
