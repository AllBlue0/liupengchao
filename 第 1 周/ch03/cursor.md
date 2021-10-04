# cursor

对于CursorAlloc()，就是把0的下一个赋值给P，并把P的下一个赋值给0，实际上就是把P从freelist中删除。对于CursorFree()，就是把0的下一个赋值给P的下一个，然后把P赋值给0的下一个，实际上就是把P加入freelist。注意，P，CursorSpace[0].Next,CursorSpace[P].Next的实际类型都是int。
