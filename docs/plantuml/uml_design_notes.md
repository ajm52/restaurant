# UML Restaurant Design Notes

author: ajm
created: 2/4/20
last modified: 2/4/20

The following information shall be used as a reminder of how to describe things well in PlantUML.

Links used:

- https://plantuml.com/class-diagram

- https://www.visual-paradigm.com/guide/uml-unified-modeling-language/uml-aggregation-vs-composition/

**Class Relationships**

Association: Appropriate when two classes need to communicate with each other.

Aggregation and Composition are both subsets of Association, where one class "owns" another.

- Composition implies a relationship where the owned class CANNOT exist without the owner class.
  • Ex: A Room cannot exist without a Building.

- Aggregation implies Composition, except the owned class CAN exist without the owner class.
  • Ex: A Student may exist outside the Classroom.
