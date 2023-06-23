 else if (target < middle->data.id) {
        binarySearch(queue, target, left, middle->prev);
    } else {
        binarySearch(queue, target, middle->next, right);
    }