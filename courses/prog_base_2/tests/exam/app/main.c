#include <stdio.h>
#include <stdlib.h>

#include "list.h"
#include "blog.h"



int main(void)
{
    blog_t blog = blog_new();
    user_t me = user_new(blog);
    printf("%d", user_getSelfId(me));
    return 0;
}
