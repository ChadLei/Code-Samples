
'''
Removes all occurrences of a item in a list contained in another list
Function takes 2 lists as inputs:
    - originalList: the list to remove items from (if any)
    - listToCheckAgainst: the list containing items that might be in originalList 
'''
def removeDuplicates ( originalList, listToCheckAgainst ):
    
    newList = originalList[:] # first creates a copy of the original list
    for i in originalList:
        for k in listToCheckAgainst:
            if i == k:
                newList[:] = [item for item in newList if item != i] # delete occurrences in the copy only
    originalList[:] = newList # set the old list to the newly 'cleaned' up list


     




if __name__ == "__main__":
##    list1 = ['a', 'a', 'b', 'c', 'd', 'c', 'e', 'f', 'f']
##    list2 = ['c', 'e', 'f']
##    list1 = [1,5,2,3,7,4,5,5,6,7,8]
    list1 = [1,2,3,4,5,6,7,8]
    list2 = [1,2,3,7,8]
    removeDuplicates (list1, list2)
    print(list1)
