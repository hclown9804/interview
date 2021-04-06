```java
/**
 * Definition for singly-linked list.
 * public class ListNode {
 *     int val;
 *     ListNode next;
 *     ListNode(int x) { val = x; }
 * }
 */
class Solution {
    public ListNode getKthFromEnd(ListNode head, int k) {
        ListNode l1 = head, l2 = head;
        while (k-- > 0) l1 = l1.next;
        while (l1 != null) {
            l1 = l1.next;
            l2 = l2.next;
        }
        return l2;
    }
}
```

