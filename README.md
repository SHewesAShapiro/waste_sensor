# waste_sensor
senses the level in a waste flask and creates an alert

Abstract:
Waste flasks fill up fast in labs that do a lot of cell culture. Keeping track of waste is a tedious task that causes conflict if lab members forget or neglect this chore. The waste flask can also overflow if seriously neglected, causing damage to the system. We propose to create a simple light-based sensor and alert system. This will sense whether the waste level is above a certain level, indicating that it is time for the container to be emptied. It will then email the lab member who is next in line to empty it. It will send several reminders and then threaten to email the member's boss if the alert goes unanswered.

Brainstorm:
getting people to empty waste flasks is a pain and causes lab drama
With an automated system you decrease the need to have awkward conversations with your labmates and strain relationships
You can't claim it's not your turn because the system knows who's next! You can't claim you forgot because the system keeps track

a simple light sensor will give an alert when a flask is full
It will sense a difference in air in your flask compared to clear liquid (or any non-air thing inside the beaker) - could be non-clear liquid
It will do a check every minute to see the status of the flask

It will then send you several email reminders until you do it
If you don't, it will threaten to -- and ultimately will -- email your boss!
