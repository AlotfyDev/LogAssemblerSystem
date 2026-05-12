14. Required Taxonomy Updates Before Final Artifacts
14.1 Additions to Core / Boundary Entities
14.1.1

The next taxonomy revision should add:

Proposed ID	Entity	Recommended Layer
E-INT-011	Envelope Assembler	Core Internal / Contract-Side Composite
E-INT-012	Assembler Ingress Port	Core Internal Boundary Port
E-INT-013	Administrative / Ecosystem Port	Core Internal Boundary Port
E-INT-014	Registry / Delivery Port	Core Internal Boundary Port
14.2 Potential Carrier/Object Additions
14.2.1

The next boundary/carrier object layer may also add:

Proposed ID	Object	Nature
BCO-012	Log Level Envelope	client-side produced envelope payload / ingress payload carrier
BCO-013	Delivery-Cycle Flag Set	dispatcher state artifact
BCO-014	Dispatcher Feedback Report	diagnostic/reporting artifact
14.3 Reason
14.3.1

These were not explicit in the earlier taxonomy.

14.3.2

They became necessary because Batch 4 delegation requires precise responsibility carriers and governed artifacts.