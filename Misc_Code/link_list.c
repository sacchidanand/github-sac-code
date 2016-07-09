#include<stdio.h>
#include<stdlib.h>

struct node
{
  struct node *next;
  int item;
};
typedef struct node node;

int insert_item(node **start, int item)
{
  node *current, *head;

  current = (node*) malloc(sizeof(node));
  current->item = item;
  current->next= NULL;
  
  /* If list is non-empty*/
  if(*start != NULL)
  {
    head = *start;
    while(head->next != NULL)
    {
      head = head->next;
    }
    head->next = current;
  }
  else
  {
    *start = current;
  }

  return 0;
}

int search_item(node **start, int item)
{
  node *current = (node*)*start;
  if(current != NULL)
  {
    /*Traverse the linked list*/
    while(current != NULL && current->item != item)
    {
      current = current->next;
    }

    /* Check if the item is found or not*/  
    if(current != NULL && current->item == item)
    {
      printf("\n Item is present in the linked list \n");
      return 1;
    }
    else
    {
      printf("\n Item is absent in the linked list \n");
    }

  }
  else
  {
    printf("\n List is empty \n");
  }
  return 0;
}

int delete_item(node **start, int item)
{
  node *current;
  if(*start != NULL)
  {
    current = *start;
    node *successor = current->next;

    int deleted_node = 0;
    deleted_node = search_item(start, item);

    if(deleted_node == 1)
    {
      if((current->item == item) && (successor == NULL))
      {
        printf("\n Deleted item : %d", current->item);
        free(current);
        return 0;
      }

      /*Traverse the linked list*/
      while(successor->item != item && successor != NULL)
      {
        successor = successor->next;
        current = current->next;
      }

      /* Check if the item is found or not*/  
      if(successor != NULL)
      {
        current->next = current->next->next;
        printf("\n Deleted item : %d \n", successor->item);
        free(successor);
      }
    }
    else
    {
      printf("\n Item is not present for deletion");
    }
  }
  else
  {
    printf("\n List is empty");
  }
  return 0;
}


int display_linked_list(node **start)
{  
  node *current = (node*)*start;
  if(current != NULL)
  {
    /*Traverse the linked list*/
    printf("\n Linked list is as follows : ");
    while(current != NULL)
    {
      printf("%d ", (current)->item);
      current = current->next;
    }
    printf(" NULL \n");
  }
  else
  {
    printf("\n List is empty");
  }
  return 0;
}

int reverse_linked_list(node **start)
{
   node *one, *two, *three;

   one = NULL;
   two = *start;
   three = two->next;

   if(three == NULL)
   {
     two->next = one;
   }

   while(three != NULL)
   {
      two->next = one;
      one = two;
      two = three;

      if(three != NULL)
      {
        three = three->next;
      }

      if((three == NULL) && (two != NULL))
      {
         two->next = one;
         *start = two;
         break;
      }
      *start = two;
   }
  return 0;
}

int main()
{
  node *start = NULL;
  int input = 0, item = 0;


    insert_item(&start, 12);
    display_linked_list(&start);
    insert_item(&start, 13);
    display_linked_list(&start);
    insert_item(&start, 14);
    display_linked_list(&start);

  while(1)
  {
    printf(" ****************************************************************** \n\n \
        \n Enter an choice as follow \n 1. Insert an item \
        \n 2. Delete an item \n 3. Search an item  \
        \n 4. Reverse a linked list \n 5. Display a linked list \
        \n 9. Exit the application. \n\n Please enter choice : ");
    scanf("%d", &input);

    switch(input)
    {
      case 1: 
        printf("\n\n Enter a number for insertion : ");
        scanf("%d",&item);
        insert_item(&start, item);
        break;
      case 2: 
        printf("\n\n Enter a number for deletion : ");
        scanf("%d",&item);
        delete_item(&start, item);
        break;
      case 3: 
        printf("\n\n Enter a number for searching : ");
        scanf("%d",&item);
        search_item(&start, item);
        break;
      case 4: 
        reverse_linked_list(&start);
        break;
      case 5: 
        display_linked_list(&start);
        break;
      case 9: break;
      default: printf(" \n\n Enter a valid input \n");
               break;
    }
    if((input == 9) || !(input == 1 || input == 2 || input == 3 || input == 4 || input == 5))
    {
      break;
    }
  }
  
  return 0;
}










