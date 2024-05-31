# Problem statement

Create a list of people that should be invited to a party. Each relationship is given as a tuple (A, B, cond), where A and B are different people and cond is one of the following:

- 0: invite one or both
- 1: invite both or neither
- 2: smae as 1
- 3: exclude one or both

# Algorithm

```
Create empty invitee list
LOOP over relationships
    IF relationship != 0
        CONTINUE
    LOOP P over A and B
        Add P to test list  T = previous accepted list + P
        If T valid
           Add P to invitee list
```
     
    
