
- binary search

二分法，区间的定义一般为两种，左闭右闭即[left, right]，或者左闭右开即[left, right)。

**左闭右闭**

左闭右闭的区间，循环不变量要写成:

while (left <= right)  因为 right 要包含在内, right = nums.size() - 1;

当 nums[middle] > target 时，right = middle - 1, 因为右闭时middle 已经包含过了。

当 nums[middle] < target 时，left = middle + 1

**左闭右开**

循环不变量写成:

while (left < right) right 不包含在内, right = nums.size();

当 nums[middle] > target 时, right = middle

当 nums[middle] < target 时, left = middle + 1;

<a href="704.cpp">704. 二分查找</a>

<a href="35.cpp">35. 搜索插入位置</a>

<a href="34.cpp">34. 在排序数组中查找元素的第一个和最后一个位置</a>

<a href="69.cpp">69. Sqrt(x)</a>

<a href="367.cpp">367. 有效的完全平方数</a>

<a href="278.cpp">278. 第一个错误的版本</a>

<a href="374.cpp">374. 猜数字大小</a>

<a href="744.cpp">744. 寻找比目标字母大的最小字母</a>

<a href="1064.cpp">1064. 不动点</a>

<a href="1099.cpp">1099. 小于 K 的两数之和</a>

<a href="1150.cpp">1150. 检查一个数是否在数组中占绝大多数</a>

<a href="1213.cpp">1213. 三个有序数组的交集</a>

<a href="1337.cpp">1337. 矩阵中战斗力最弱的 K 行</a>

<a href="1346.cpp">1346. 检查整数及其两倍数是否存在</a>

<a href="1385.cpp">1385. 两个数组间的距离值</a>

<a href="1608.cpp">1608. 特殊数组的特征值</a>

<a href="0803.cpp">面试题 08.03. 魔术索引</a>

<a href="068.cpp">剑指 Offer II 068. 查找插入位置</a>

<a href="2089.cpp">2089. 找出数组排序后的目标下标</a>

<a href="349.cpp">349. 两个数组的交集</a>

<a href="350.cpp">350. 两个数组的交集 II</a>
