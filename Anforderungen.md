# Projekt 3

Um in der Notaufnahme eines Krankenhauses die Patienten bestmöglich versorgen zu können,
ist es notwendig die Patienten zu priorisieren. Zusätzlich zu der Priorisierung soll den Patienten
wenn möglich ein Sitzplatz zugeordnet werden. Das Programm, das Sie erstellen sollen, arbeitet mit einem einfachen Modus für die Priorisierung. Personen, die mit einem Krankenwagen
gebracht werden, werden vor Personen behandelt, die selbstständig in die Notaufnahme kommen. Personen die selbst in die Notaufnahme kommen, müssen einen Sitzplatz zugewiesen
bekommen. Dadurch soll sicher gestellt werden, dass auch nachträglich festgestellt werden
kann, welche Sitznachbarn eine Person hatte. Dies ist zwingend Notwendig, um im Falle einer
nachgewiesenen Erkrankung mit einer ansteckenden Krankheit, die Sitznachbarn verständigen zu können. Sie können Annehmen, dass 25 Sitzplätze in einem 5x5 Muster aufgestellt
sind. Zwischen den Sitzteihen ist genug Platz, dass eine Nachverfolgung dieser Sitznachbarn
nicht notwendig ist. Damit ist nur eine Nachverfolgung der Sitznachbarn innerhalb der Sitzreihe
notwendig. Personen die mit der Rettung in die Notaufnahme gebracht werden, brauchen keinen Sitzplatz.

## Folgende Aufgaben muss das Programm erfüllen:
- Es muss ein User Interface implementiert werden.
- Hinzufügen von Patienten, die selbstständig in die Notaufnahme gekommen sind.
- Hinzufügen von Patienten, die durch einen Krankenwagen in die Notaufnahme gekommen sind.
- Entfernen eines Patienten durch eine erfolgreiche Behandlung. Dies muss nach der definierten Priorisierung erfolgen.
- Nachträgliches Abfragen welche Sitzpartner ein Patient hat. Sollte kein Sitzplatz zugewiesen worden sein, sind keine Sitzpartner zurück zu geben.