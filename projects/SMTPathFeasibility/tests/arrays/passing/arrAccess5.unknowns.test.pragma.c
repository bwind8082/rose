int main(int d) {
	#pragma p1_reachable begin infeasible
	#pragma p2_reachable begin infeasible
	#pragma p3_unreachable begin infeasible
	int a[5];
	a[1] = 2;
	a[2] = 3;
	if (d == 2) {
		#pragma p1_reachable end
		a[1] = 3;
	}
	if (a[1] == 3) {
		#pragma p2_reachable end
		a[1] = d + 3;
	}
	if (a[2] != 3) {
		#pragma p3_unreachable end
		d = d + 1;
	}
	return 0;
}
