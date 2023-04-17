#include <stdio.h>
#include <stdlib.h>
#include "../include/CSV_read.h"



int csv_read(){
	
		//open file + error handling
		FILE *file = fopen("test.csv", "r");

		if (file == NULL) {
			printf("Error opening file.\n");
			return 1;
		}
		//create 100 patient records
		PatientRecord Patient[100];
		// ead= "value-counter" for iteration through the csv file
		int read = 0;
		// == lines/patients
		int records = 0;
		// read and store all infomration into the struct until eof
		do {

			read = fscanf(file, "%i,%49[^,],%5[^,],%5[^,],%c,%i\n",
					&Patient[records].ssn,
					Patient[records].name,
					Patient[records].arrival_time,
					Patient[records].departure_time,
					&Patient[records].infectious,
					&Patient[records].seating_number);

			// patient has 6 struct-elements, if read =6 store the following information to the next patient
			if (read == 6)
				records++;

			//if file format incorrect or eof error handling
			if (read != 6 && !feof(file)) {
				printf("File format incorrect.\n");
				return 1;
			}
			//error handling file pointer
			if (ferror(file)) {
				printf("Error reading file.\n");
				return 1;
			}

		} while (!feof(file));

		fclose(file);
		//print out the patients
		printf("\n%d records read.\n\n", records);
		int index=1;
		for (int i = 0; i < records; i++){
			printf("%i: %i, %s, %s, %s, %c, %i\n",
					index,
					Patient[i].ssn,
					Patient[i].name,
					Patient[i].arrival_time,
					Patient[i].departure_time,
					Patient[i].infectious,
					Patient[i].seating_number);
			index++;
		}
		printf("\n");

		return 0;
}
