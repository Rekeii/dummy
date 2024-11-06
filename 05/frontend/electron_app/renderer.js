const addon = require('../addon/build/Release/addon');

// Function to get product details
function getProduct() {
    const id = document.getElementById("productId").value;
    if (!id) {
        alert("Please enter a valid product ID.");
        return;
    }
    try {
        const product = addon.getProduct(id);
        alert(`Product Details: ${product}`);
    } catch (error) {
        console.error("Error getting product:", error);
        alert("Failed to get product details.");
    }
}

// Function to add a new product
function addProduct() {
    const productData = document.getElementById("productData").value;
    try {
        const productJson = JSON.parse(productData);
        const result = addon.addProduct(productJson);
        alert("Product added successfully.");
    } catch (error) {
        console.error("Error adding product:", error);
        alert("Failed to add product. Ensure JSON format is correct.");
    }
}

// Function to update an existing product
function updateProduct() {
    const id = document.getElementById("productId").value;
    const productData = document.getElementById("productData").value;
    if (!id) {
        alert("Please enter a valid product ID.");
        return;
    }
    try {
        const productJson = JSON.parse(productData);
        const result = addon.updateProduct(id, productJson);
        alert("Product updated successfully.");
    } catch (error) {
        console.error("Error updating product:", error);
        alert("Failed to update product. Ensure JSON format is correct.");
    }
}

// Function to delete a product
function deleteProduct() {
    const id = document.getElementById("productId").value;
    if (!id) {
        alert("Please enter a valid product ID.");
        return;
    }
    try {
        const result = addon.deleteProduct(id);
        alert("Product deleted successfully.");
    } catch (error) {
        console.error("Error deleting product:", error);
        alert("Failed to delete product.");
    }
}
