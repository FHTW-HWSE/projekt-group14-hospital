# projekt-group14-hospital
projekt-group14-hospital created by GitHub Classroom


## General Information
* Distinguishing normal Patient/priority patient: seating Number -1 = priority patient => Arrived by Abulance

# **User Stories**


## Prioritizing Patients Based on Arrival Method

>**As a** nurse/hospital employee <br>
**I want** to see how the patients arrived at the hospital <br>
**So that** I can prioritise patients <br>

- **Given**: A patient arrives by ambulance
- **When**: Registered by a nurse 
- **Then**: 
  - They are prioritized (treated before people who arrive independently) (and)
  - Program updates & outputs the prioritization list 

## >> If a patient is registered the program automatically updates the database & Prio list can be printed out in the menu  'p' 

<br>
 
- **Given**: A patient arrives independently 
- **When**: Registered by a nurse 
- **Then**: 
  - A seat must be assigned (and) 
  - Program ensures that a seat is only occupied once & seating is printed out 

## >> Program ensures that a seat is only occupied once & seating map can be displayed in the menu 'm'
 

## Waiting Room Map for Organizing Patient Seating

>**As a** nurse/hospital employee <br>
**I want** to have a map of the waiting room in a separate menu   <br>
**So that** I can organize the sitting order of the patients  <br>

- **Given**: Program has been started
- **When**: Hospital employee is in the menu and opens the map 
- **Then**: Program shows a map of the waiting area & shows seating 

## >> Map can be opened in the menu 'm'

 <br>

## Removing Treated Patients

>**As a** nurse/hospital employee <br>
**I want** to be able to remove patients after they are treated <br>
**So that** I can check in new patients <br>

- **Given**: The patient has been treated 
- **When**: Is ready to leave the hospital 
- **Then**: 
  - Prioritising should be deleted (Program checks if patient is no longer on the list)
  OR
  - Seat should be released and free again for the next person 

## >> Patients can be removed in the menu 't' & seats will be freed & due to the added departure time & date the patient will not longer be displayed in the prio list
<br>

## Marking Patients with Infectious Diseases for Tracking Purposes


>**As a** nurse/hospital employee <br>
**I want** to be able to mark a patient as having an infectious disease at the time of the stay <br>
**So that** I can track the infectious patients which stay at our hospital.  <br>

- **Given**: A patient has informed me that they had been infectious during the stay. 
- **When**: I select that the patient has been infectious in the menu  
- **Then**: A “Infectious disease” mark will be added to the patient's file/ dB entry.  

## >> In the menu 'c' the user can change the infectious "status" 
<br>

- **Given**: Patient had seating neighbours 
- **When**: An “Infectious disease” mark has been set in the patient data  
- **Then**: The Surrounding patients should automatically get added a “contact person” mark. 
 
 ## >> surrounding patients are not getting a contact person mark
<br>

## Printing Contact Persons of a Patient for Contact Tracing

 

>**As a** nurse/hospital employee <br>
**I want** to be able to print the contact persons of a given patient to my screen <br>
**So that** I can the inform the patients which sat next to the person that they should stay at home <br>


- **Given**: 
  - A patient had seating neighbours, and 
  - A patient has an “Infectious disease” mark set in their patient data 
- **When**: I enter the patients name in the corresponding menu 
- **Then**: The names of the seating neighbours will be printed to the screen 

## >> Menu 'i' the user enters the SSN and the seating neighbours will be displayed
<br><br>
- **Given**: A patient had no seating neighbours 
- **When**: I enter the patients name in the corresponding menu 
- **Then**: A “no seating neighbours” message will be displayed 

## >> Menu 'i' if patient had no seating neighbours the message "No seating neigbours found" is printed out
<br>

## Viewing List of Patients in the Waiting Room
 
>**As a** hospital employee  <br>
**I want** to be able to view the list of patients in the waiting room  <br>
**So that** I can keep track of who needs to be treated next <br>

## >> Menu 'w' shows a list of the patients who are currently in the waiting room

- **Given**: The program is running 
- **When**: I select the option to view the list of patients in the waiting room 
- **Then**: The program displays a list of patients in order of priority, with ambulance patients listed first 

<br>

## Viewing Patient Information and Status

>**As a** hospital employee <br>
**I want** to be able to view a patient's information and status <br>
**So that** I have an overview <br>

- **Given**: A patient is registered in the system
- **When**: select the patient's name in the patient list
- **Then**: The patient's information should be displayed along with their current status (waiting, discharged)

## >> In menu 's' the user can search for a patient and see their information
<br>

## Registering Patient Information for Database and Contact Purposes

>**As a** hospital employee <br>
**I want** to register the patient information for the database and contact informations <br>
**So that** I have the personal data of the patient that needs to be treated <br>

- **Given**: A patient arrived 
- **When**: The patient needs to be treated
- **Then**: Program shows a form that can be filled out with information of the patient  creates a new database entry. 

## >> In menu 'n' the user can create a new patient
<br>

## Updating Patient Information

>**As a** nurse/hospital employee  <br>
**I want** to be able to update a patient's information after they have been registered  <br>
**So that** I can keep their information up to date <br>

- **Given**: A patient has been registered in the program 
- **When**: I select the "update patient information" option from the menu 
- **Then**: I can edit of the patient's infectious status

## >> In menu 'c' the user can change the infectious status of a patient 
<br>
<br>
 
