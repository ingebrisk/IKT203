# README

## PART 1.3 - Why Single Linked List?
In this task I chose to use a single linked since it does not matter what order the accounts is stored, and it is easy to search through the list. A single linked list is efficient in memory management and use less memory then the double linked list. The double linked list would be more efficient if wee needed to get the accounts from the back and easily remove accounts from inside the list and not at the end. The circular linked list would also be unnecessary because we are doing searches through the list to find the element once. we don’t need to find them more than that.  

## PART 4.11
The names are made in a array instead of a generator on the internet. The array is populated to 70 first names and 70 last names which makes 4900 name combinations. A weakness to this approche is that the same name chould be generated more than once and some people can than get more then 10 accounts. Therefor the methode of visited from task 4. So the same name whould not be used again and again. 

## PART 4.12
The number of comparison for `find()` and every account made is linear and therefor has the complexity **O(n)**. It will search through the list once it find a match it will stopp. If it dont find a match it will end at the line. In short the number of compairesin is therfor the same as the position of the account in the list. 

The difference in flexibility of `Every()` and `PrintEveryAccountInDateRange()`. `Every()` is dynamic and does not know if it searches for dates or names. However `PrintEveryAccountInDateRange()` is statick and only print everything between two date times. `Every()` dont print out anything without you specifically askes it to do so, but `PrintEveryAccountInDateRange()` writes alle the accounts out. 