#include<iostream>
#include<cstdio>
#include<cstdlib>
using namespace std;

template <typename T>
class Queue {

private:
	struct Element {
		T data;
		Element *next;
		Element *previous;
	} _element;
	int _size;
	Element *_HEAD;
	Element *_TAIL;

public:
	Queue(): _size(0), _HEAD(NULL), _TAIL(NULL) {};
	~Queue() {};
	void push(T data) {
		if (_size == 0) {
			Element *newElement = new Element;
			newElement->data = data;
			newElement->next = NULL;
			_TAIL = newElement;
			_HEAD = newElement;
			_size = 1;
		} else {
			Element *newElement = new Element;
			newElement->data = data;
			newElement->next = NULL;
			_TAIL->next = newElement;
			_TAIL = newElement;
			_size++;
		}
	};
	T pop() {
		if (_size ==  0) {
			return T();
		} else {
			T oldData = _HEAD->data;
			Element *oldElement = _HEAD;
			_HEAD = _HEAD->next;
			delete oldElement;
			if (_HEAD == NULL) {
				_TAIL = NULL;
			}
			_size--;
			return oldData;
		}
	};
	T front() {
		if (_size == 0) {
			return T();
		} else {
			return _HEAD->data;
		}
	}
	int size() {
		return _size;
	};
};

struct Plane {
	int id;
	int startTime;
	int leftTime;
};

int main() {
	Queue<Plane> landQueue, takeoffQueue;
	int runwayNum = 0, landTime = 0, takeoffTime = 0;
	int currentLand = 0, currentTakeoff = 0, currentTime = 0;
	int landSum = 0, takeoffSum = 0, landTimeSum = 0, takeoffTimeSum = 0, planeSum = 0;
	cin >> runwayNum >> landTime >> takeoffTime;
	int **runwayStatus = (int **)malloc((runwayNum + 5) * sizeof(int *));
	for (int i = 0; i < runwayNum; i++) {
		runwayStatus[i] = (int *)malloc(2 * sizeof(int));
		runwayStatus[i][0] = 0;
		runwayStatus[i][1] = 0;
	}
	Plane *workingPlane = (Plane *)malloc((runwayNum + 5) * sizeof(Plane));
	printf("Current Time: %4d\n", currentTime);
	cin >> currentLand >> currentTakeoff;
	while (currentLand != -1 && currentTakeoff != -1) {
		landSum += currentLand, takeoffSum += currentTakeoff, planeSum += currentLand + currentTakeoff;
		for (int i = 0; i < currentLand; i++) {
			Plane newLand;
			newLand.id = landSum - currentLand + i + 5001;
			newLand.startTime = currentTime;
			newLand.leftTime = landTime;
			landQueue.push(newLand);
		}
		for (int i = 0; i < currentTakeoff; i++) {
			Plane newTakeoff;
			newTakeoff.id = takeoffSum - currentTakeoff + i + 1;
			newTakeoff.startTime = currentTime;
			newTakeoff.leftTime = takeoffTime;
			takeoffQueue.push(newTakeoff);
		}
		for (int i = 0; i < runwayNum; i++) {
			if (runwayStatus[i][0] == 0) {
				if (landQueue.size() != 0) {
					workingPlane[i] = landQueue.pop();
					runwayStatus[i][0] = 1;
					printf("airplane %04d is ready to land on runway %02d\n", workingPlane[i].id, i + 1);
					landTimeSum += currentTime - workingPlane[i].startTime;
					//planeSum--;
					workingPlane[i].leftTime--;
				} else if (takeoffQueue.size() != 0) {
					workingPlane[i] = takeoffQueue.pop();
					runwayStatus[i][0] = 1;
					printf("airplane %04d is ready to takeoff on runway %02d\n", workingPlane[i].id, i + 1);
					takeoffTimeSum += currentTime - workingPlane[i].startTime;
					//planeSum--;
					workingPlane[i].leftTime--;
				}
			}
		}
		currentTime++;
		printf("Current Time: %4d\n", currentTime);
		for (int i = 0; i < runwayNum; i++) {
			if (runwayStatus[i][0] == 1) {
				if (workingPlane[i].leftTime == 0) {
					printf("runway %02d is free\n", i + 1);
					planeSum--;
					runwayStatus[i][0] = 0;
					runwayStatus[i][1]++;
				} else {
					workingPlane[i].leftTime--;
					runwayStatus[i][1]++;
				}
			}
		}
		cin >> currentLand >> currentTakeoff;
	}
	while (planeSum) {
		for (int i = 0; i < runwayNum; i++) {
			if (runwayStatus[i][0] == 0) {
				if (landQueue.size() != 0) {
					workingPlane[i] = landQueue.pop();
					runwayStatus[i][0] = 1;
					printf("airplane %04d is ready to land on runway %02d\n", workingPlane[i].id, i + 1);
					landTimeSum += currentTime - workingPlane[i].startTime;
					//planeSum--;
					workingPlane[i].leftTime--;
				} else if (takeoffQueue.size() != 0) {
					workingPlane[i] = takeoffQueue.pop();
					runwayStatus[i][0] = 1;
					printf("airplane %04d is ready to takeoff on runway %02d\n", workingPlane[i].id, i + 1);
					takeoffTimeSum += currentTime - workingPlane[i].startTime;
					//planeSum--;
					workingPlane[i].leftTime--;
				}
			}
		}
		currentTime++;
		printf("Current Time: %4d\n", currentTime);
		for (int i = 0; i < runwayNum; i++) {
			if (runwayStatus[i][0] == 1) {
				if (workingPlane[i].leftTime == 0) {
					printf("runway %02d is free\n", i + 1);
					planeSum--;
					runwayStatus[i][0] = 0;
					runwayStatus[i][1]++;
				} else {
					workingPlane[i].leftTime--;
					runwayStatus[i][1]++;
				}
			}
		}
	}
	float landTimeSumF = landTimeSum, takeoffTimeSumF = takeoffTimeSum, occTime = 0;;
	printf("simulation finished\nsimulation time: %4d\n", currentTime);
	printf("average waiting time of landing: %4.1f\naverage waiting time of takeoff: %4.1f\n", landTimeSumF / landSum, takeoffTimeSumF / takeoffSum);
	for (int i = 0; i < runwayNum; i++) {
		printf("runway %02d busy time: %4d\n", i + 1, runwayStatus[i][1]);
		occTime += runwayStatus[i][1];
	}
	occTime /= runwayNum;
	printf("runway average busy time percentage: %4.1f%\n", occTime * 100 / currentTime);
	return 0;
}

