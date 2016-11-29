<?php
class KW
{
  protected $tag;
  protected $datum;
  private   $KW;
  private   $jahr;
  private   $montag;
  private   $wochenTag;
  private   $tagNachKW;
  private   $tagVorKW;

  function __construct($strDate) // Format 'yyyy-mm-dd'
  {
    date_default_timezone_set('Europe/Berlin');
    $this->tag = array (
      "--" => "",
      "Mo" => "",
      "Di" => "",
      "Mi" => "",
      "Do" => "",
      "Fr" => "",
      "Sa" => "",
      "So" => "",
    );
    $this->datum = new DateTime(date( $strDate ));
    $this->KW = $this->datum->format( "W" );
    $this->jahr = $this->datum->format( "y" );
    $this->wochenTag = $this->datum->format( "w" );
    $c = 0;
    unset($this->tagVorKW);
    foreach ($this->tag as $key => &$value)
    {
      $datum = new DateTime($this->datum->format( "Y-m-d" ));
      if( $c == $this->wochenTag )
      {
        $value = $datum->format("d.m."); // vormals: "j.n." (tag.monat. ohne fuehrende null)"d.m."
	if( !$c ) // Wochentag 0 = Sonntag (im Vektor: "--" )
	  $this->tagVorKW = date_sub($datum,date_interval_create_from_date_string( "1 days" ));
      }
      else if( $c < $this->wochenTag )
      {
        
        date_sub($datum,date_interval_create_from_date_string( $this->wochenTag - $c . " days" ));
        $value = $datum->format("d.m.");
	if( !isset($this->tagVorKW) ) // Wochentag 0 = Sonntag (im Vektor: "--" )
          $this->tagVorKW = date_sub($datum,date_interval_create_from_date_string( "1 days" ));
      }
      else if( $c > $this->wochenTag )
      {
        date_add($datum,date_interval_create_from_date_string( $c - $this->wochenTag . " days" ));
        $value = $datum->format("d.m."); // im letzten Durchlauf ist das der "So" im Vektor
        $this->tagNachKW = date_add($datum,date_interval_create_from_date_string( "1 days" ));
      }
      ++$c;
    }
    $datum = new DateTime($this->tagVorKW->format( "Y-m-d" ));
    $this->montag = date_add($datum,date_interval_create_from_date_string( "2 days" ));
  }
  function __get($var)
  {
    switch($var)
    {
      case 'Datum':
        return $this->datum->format("Y-m-d");
      case 'DatumEU':
        return $this->datum->format("d.m.Y");
      case 'Jahr':
        return $this->jahr;
      case 'Kalenderwoche':
        return $this->KW;
      case 'KWweiter':
        return $this->tagNachKW->format("Y-m-d");
      case 'KWzurueck':
        return $this->tagVorKW->format("Y-m-d");
      case 'Montag':
        return $this->montag->format("d");
      case 'Wochentag':
        return $this->tag[$this->wochenTag];
      case 'WochentagNumerisch':
        return $this->wochenTag;
      case 'eilt':
        //return parent::__get('eilt');
      default:
        throw new Exception("KW hat keine Eigenschaft $var.", 1 );
      break;
    }
  }
}
