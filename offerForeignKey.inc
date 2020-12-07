<?php
$arrFK = array(
/*zum Kopieren:
	""=>array( // ich bin die Entitaet
		"",// ich bin ein Fremdschluessel
	),
*/
	"Ort"=>array( // ich bin die Entitaet
		"Trainer",// ich bin ein Fremdschluessel
	),
	"ProbandOrt"=>array( // ich bin die Entitaet
		"Behoerde",// ich bin ein Fremdschluessel
	),
	"Proband"=>array( // ich bin die Entitaet
		"ProbandOrt",// ich bin ein Fremdschluessel
	),
	"ProbandBehoerde"=>array( // ich bin die Entitaet
		"Behoerde",// ich bin ein Fremdschluessel
	),
	"ProbandMail"=>array( // ich bin die Entitaet
		"Mail",// ich bin ein Fremdschluessel
	),
	"ProbandMassnahme"=>array( // ich bin die Entitaet
		"Massnahme",// ich bin ein Fremdschluessel
	),
	"Termin"=>array(
		"Ort",// ich bin ein Fremdschluessel
		"Terminart",
		"Kategorie",
		"Jahr",
		"KW",
		"Tag",
		"Trainer",
		"VS",
	),
	"Vormerkung"=>array( // ich bin die Entitaet
		"Ort",// ich bin ein Fremdschluessel
	),
);
?>
