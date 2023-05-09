#### Discussion points
- CLOCS check?
- Driver induction form needs to be printed to PDF?
- Functionality of slot durations?
- Summarized data on the dashboard home
- FORS integration: only forsBadge is being fetched from the API
- Please provide list of the global unload methods
- Reports
	- Co2Emissions
		- Report cannot be generated if FORS is disabled for a site
		- What is the usage of gate and crane for this report
	- Other reports
		- involvement of Gate and Crane?
	- Export to excel required?


#### Scope enhancements & changes
- manage companies: (subcontractors work for companies)
	- Frontend
	- Backend (complete)
- booking forms: trade contractor name should be drop-down for company (backend complete)
- keep track of which delivery was actioned (metadata) by which gatekeeper.
- Driver induction:
	- Form: driver will fill out this form at the time of arrival at site
		- Link induction form to delivery
		- terms and conditions: boolean
		- illnesses: boolean
		- driver name
		- company
		- signature
		- date
	- List all inductions (paginate)
	- List for date
- On-the-spot deliveries: Driver will manually obtain the approval and book the delivery himself.
- Gatekeeper multiple-assignments (complete)
	- Allow site manager to search all gatekeepers in the system by their email address
	- Add / remove gatekeeper to site
- automatically mark (normal) pending deliveries as NODELIVERY, when site timing ends


# TODO
- Front-end
	- Site options form
		- move concrete checkbox from resources to site options
		- combine disabled days checkboxes into a single multi-select drop-down
	- Resource booking form
		- Delivery date / time / duration (H:M) is mandatory, don't allow checking resource availability without these field filled-out
		- Material of notes (add) modal
		- Redesign of the materials movement section
			- Resource availability modal dialog
	- Delivery booking form
		- Delivery date / time / duration (H:M) is mandatory, don't allow checking resource availability without these field filled-out
		- Material of notes (add) modal
		- Fors section is optional: hide if FORS is disabled for the site
		- Redesign of the materials movement section
			- Resource availability modal dialog
		

# sample FORS Ids
001387            FORS Silver
000385            FORS Gold


# resources breakdown
name                    isResource?
-----------------------------------------------------
Gate                    Yes 		(delivery only)
Offloading bay          Yes
Laydown area            Yes			(delivery only)
Hoist                   Yes
Crane                   Yes
Forklift                Yes
Meeting rooms           Yes			(resource booking only)
Elevator                Yes
Concrete                -			(delivery only)
Unload method           -
Material of notes       -
Final destination       -
Edge protection         -
