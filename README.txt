Workbench Moderation
====================

About this module
-----------------
Workbench Moderation (WBM) provides basic moderation support for revisionable content entities.  That is, it allows
site administrators to define States that content can be in, Transitions between those States, and rules around who
is able to transition content from one State to another, when.

In concept, any revision-aware content entity is supportable.  In core, that includes Nodes and Block Content. However,
there is a small amount of work needed to support additional content entities due to inconsistencies in core. If your
content entity needs to be supported, please file an issue.




States
------

States are configuration entities.  A State consists of a label
