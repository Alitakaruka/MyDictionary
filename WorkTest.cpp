
#include <iostream>
#include <set>
#include <map>


template <typename Key, typename Value>
class elementD {
public:
	Key key;
	Value value;

	elementD() {}
	elementD(Key key, Value value) {
		set(key, value);
	}

#pragma region setingValues

	void set(Key key, Value value) {
		this->key = key;
		this->value = value;
	}
	void set(Key key) {
		this->key = key;
	}
#pragma endregion

#pragma region get_set_descendants

	elementD<Key, Value>* get_right_descendant() {
		return right;
	}

	elementD<Key, Value>* get_left_descendant() {
		return left;
	}

	void setRight(Key key, Value value) {
		
		this->right = new elementD<Key, Value>(key, value);
	}
	void setleft(Key key, Value value) {
		this->left = new elementD<Key, Value>(key, value);
	}
#pragma endregion

	bool operator==(const elementD<Key, Value>& obj) {
		if (this->key == obj.key)
			return true;
		return false;
	}
	void delete_right() {
		this->right = nullptr;
	}
	void delete_left() {
		this->left = nullptr;
	}
    
private:
	
	elementD* left = nullptr;
	elementD* right = nullptr;
};

#pragma region interfaces

template<class Key, class Value>
class dictionary
{
public:
	virtual ~dictionary() = default;

	virtual const Value& get(const Key& key) const = 0;
	virtual void set(const Key& key, const Value& value) = 0;
	virtual bool is_set(const Key& key) const = 0;
};

template<class Key>
class not_found_exception : public std::exception
{
public:
	virtual const Key& get_key() const noexcept = 0;
};
#pragma endregion


template<class Key, class Value>
class kDictionary :public dictionary<Key, Value>
{
public:
	kDictionary() {}
	kDictionary(Key key, Value value) {
		set(key,value);
	}
	
	~kDictionary() {
		elementD<Key, Value>* previous_element = nullptr;
		elementD<Key, Value>* now_element = root;
		while (true) {
			if (root->get_left_descendant() == nullptr && root->get_right_descendant() == nullptr) {
				delete root;
				return;
			}
			if (now_element == previous_element) {
				now_element = root;
			}
			if (now_element->get_left_descendant() == nullptr && 
				now_element->get_right_descendant() == nullptr) {

				delete now_element;
	
				if (previous_element->get_left_descendant() != nullptr) {
					previous_element->delete_left();
					now_element = previous_element;
				}
				else {
					previous_element->delete_right();
					now_element = root;
				}
				
			}
			else if (now_element->get_left_descendant() != nullptr) {
				previous_element = now_element;
				now_element = now_element->get_left_descendant();
			}
			else {
				previous_element = now_element;
				now_element = now_element->get_right_descendant();
			}
		}
	}
#pragma region overrided
	 const Value& get(const Key& key) const {
		 elementD<Key, Value>* now_element = root;
		
		 while (true) {
			 if (now_element->key == key) {
				 return  now_element->value;
			 }

			 if (now_element->get_right_descendant() == nullptr && now_element->get_left_descendant() == nullptr) {
				 return nullptr;
			 }

			 if (key > now_element->key) {
				 now_element = now_element->get_right_descendant();
			 }
			 else {
				 now_element = now_element->get_left_descendant();
			 }
		 }
		 
	 }

	 void set(const Key& key, const Value& value) {
		if (this->root == nullptr) {
			this->root = new elementD <Key, Value>(key, value);
			return;
		}

		elementD<Key, Value> *now_element = root;
		while (true) {
			if (now_element == nullptr)
				return;
			
			if (key > now_element->key) {
				if (now_element->get_right_descendant() == nullptr) 
					now_element->setRight(key,value);
				
				now_element = now_element->get_right_descendant();
				continue;
			}
			if(key < now_element->key) {
				if (now_element->get_left_descendant() == nullptr) 
					now_element->setleft(key, value);
				
				now_element = now_element->get_left_descendant();
				continue;
			}
			if (now_element->key == key) {
				now_element->value = value;
				return;
			}
		}
	}
	//Функцию find написал для себя, потом понял, что is_set почти ее копирка ¯\_(ツ)_/¯
	bool is_set(const Key& key) const {
		if (find(key) == nullptr)
			return false;

		return true;
	}

#pragma endregion


	 const elementD<Key, Value>* find(const Key& key) const{
		 elementD<Key, Value>* now_element = this->root;
		 while (true) {
			 if (now_element->key == key) {
				 return now_element;
			 }
			 if (key > now_element->key) {
				 if (now_element->get_right_descendant() == nullptr)
					 return nullptr;
				 now_element = now_element->get_right_descendant();
			 }
			 else {
				 if (now_element->get_left_descendant() == nullptr)
					 return nullptr;
				 now_element = now_element->get_left_descendant();
			 }
		 }
	 }

	bool is_root(Key key) { return key == root.key; }

	bool operator ==(const kDictionary& obj) {
		if (this->root.key == obj.root.key) {

		}
	}

protected:

private:
	
	elementD<Key, Value>* root;
};




int main()
{

}