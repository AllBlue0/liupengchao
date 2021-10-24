void printLessThanX(ElementType X, PriorityQueue h) {
	if (h) {
		if (h->element < X) {
			printf("%d ", h->element);
			printLessThanX(X, h->left);
			printLessThanX(X, h->right);
		}
	}
}
