# Ray Tracing – Mathematical Foundations

---

## 🧭 1. Basic Vector Concepts

### **Tuples, Points, and Vectors**
- A **tuple** represents coordinates or directions in space (x, y, z, w).
- A **point** has position (w = 1), while a **vector** represents direction (w = 0).
- Tuples are **immutable** and can store **heterogeneous** data.

---

### **Normalization**

**Definition:**
Normalization is the process of turning any vector into a **unit vector** (length = 1):

\[
\hat{v} = \frac{\vec{v}}{\|\vec{v}\|} = \frac{(x, y, z)}{\sqrt{x^2 + y^2 + z^2}}
\]

**Why it’s important:**
- It keeps all vectors on a common scale, ensuring consistent lighting and reflections.
- Without normalization, ray directions and surface normals would have different magnitudes, leading to distorted or incorrect lighting.

> Normalization “anchors” all calculations so that only direction — not length — matters.

---

### **Dot Product**

**Definition:**
\[
\vec{a}\cdot\vec{b} = |\vec{a}|\,|\vec{b}|\,\cos(\theta)
\]

If both vectors are **unit vectors**, then:
\[
\vec{a}\cdot\vec{b} = \cos(\theta)
\]

**Interpretation:**
- **1 →** same direction  
- **0 →** perpendicular  
- **−1 →** opposite directions  

**In ray tracing:**
The dot product tells **how much a surface “faces” the light**:

\[
\text{diffuse intensity} \propto \max(0,\, \vec{L}\cdot\vec{N})
\]

- Aligned → full light  
- Perpendicular → no light  
- Opposite → light is behind  

---

### **Cross Product**

**Definition:**
\[
\vec{a} \times \vec{b} = (a_y b_z - a_z b_y,\; a_z b_x - a_x b_z,\; a_x b_y - a_y b_x)
\]

**Meaning:**
- Produces a **vector perpendicular** to both inputs.  
- Used to compute **surface normals** and **orientation** in 3D space.  
- Crucial in geometry (e.g., generating tangent bases, camera orientation, etc.).

---

### **Scalar Multiplication / Division**

**Definition:**
\[
t\,\vec{v} = (t v_x, t v_y, t v_z)
\]

Scaling a vector by a scalar changes its **length** but not its **direction**.

**In ray tracing:**
This is how we **move along a ray** to find intersections with objects:

\[
\mathbf{P}(t) = \mathbf{O} + t\,\vec{D}
\]

Where:
- **O** = ray origin  
- **D** = normalized direction  
- **t** = distance along the ray  

> Scalar multiplication lets us locate exact points along a ray — it’s what makes intersection tests possible.

---

### **Vector Reflection**

**Definition:**
\[
\text{reflect}(\vec{i}, \vec{n}) = \vec{i} - 2(\vec{i}\cdot\vec{n})\,\vec{n}
\]

**Meaning:**
- Reverses the component of \(\vec{i}\) along \(\vec{n}\).
- Leaves tangential components unchanged.

**Examples:**
- (1, −1, 0) reflected on n = (0, 1, 0) → (1, 1, 0)
- (0, −1, 0) reflected on n = (√2/2, √2/2, 0) → (1, 0, 0)

---

## ☀️ 2. Light and Shading Concepts

### **The Four Vectors in Lighting**

| Symbol | Meaning | Definition |
|:---:|:---|:---|
| **E** | Eye vector | Points from **P** to the camera: \( \vec{E} = -\vec{d} \) |
| **L** | Light vector | From **P** to the light: \( \vec{L} = \text{light\_pos} - P \) |
| **N** | Surface normal | Perpendicular to the surface at **P** |
| **R** | Reflection vector | Direction of reflected light off the surface |

All must be **normalized**.

---

### **Surface Normals**

For a **unit sphere centered at the origin**:

\[
\vec{N}_{obj}(P) = P - O = P
\]

The normal is simply the position vector, since every point on the sphere is one unit away from the center.

---

### **Transforming Normals**

If an object is scaled, rotated, or translated, you must correctly transform its normal using the **inverse transpose** of its transform matrix:

\[
\vec{N}_{world} = \text{normalize}\!\left((\mathbf{T}^{-1})^{\top} \vec{N}_{obj}\right)
\]

- Ensures the normal remains perpendicular to the surface.
- Set \(w = 0\) (direction, not position).
- Normalize afterward.

---

### **The Phong Reflection Model**

Simulates realistic lighting using three components:

| Component | Formula | Description |
|:--|:--|:--|
| **Ambient** | \( \mathbf{A} = k_a \mathbf{c}_{eff} \) | Constant background light. |
| **Diffuse** | \( \mathbf{D} = k_d\,\mathbf{c}_{eff}\,\max(0, \vec{L}\cdot\vec{N}) \) | Matte reflection based on the light–normal angle. |
| **Specular** | \( \mathbf{S} = k_s\,\mathbf{I}\,(\max(0, \vec{R}\cdot\vec{E}))^{n} \) | Highlight reflection based on view direction and shininess. |

**Final color:**
\[
\mathbf{C} = \mathbf{A} + \mathbf{D} + \mathbf{S}
\]

---

### **Putting It All Together**

- Normalize **all** vectors before using them.
- Use **dot products** to compute lighting angles.
- Reflect incoming light vectors for **specular highlights**.
- Combine ambient, diffuse, and specular terms for realistic shading.
- Use **scalar multiplication** to march along rays and find intersections.

---

## 🧩 Summary Table

| Concept | What it does | Why it matters |
|:--|:--|:--|
| **Normalization** | Converts any vector to unit length | Keeps calculations consistent and scale-independent |
| **Dot Product** | Measures alignment between two vectors | Determines how much light hits a surface |
| **Cross Product** | Creates a perpendicular vector | Defines orientation and normals |
| **Scalar Multiplication** | Scales a vector by a number | Moves points along a ray |
| **Reflection** | Flips a vector around a normal | Simulates mirror-like bounces |
| **Phong Model** | Combines ambient, diffuse, specular | Produces realistic shading |

---

### ✨ In short:
Ray tracing relies on **vector math** to describe how light interacts with surfaces.  
Getting normalization, dot products, and transformations right is what makes your rendered images look realistic — or not render at all.
